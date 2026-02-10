#pragma once

#include <vector>

#include "const.h"
#include "AlphabetSimple.h"


class TinyString {
    std::vector<std::byte> data_{};
    std::size_t size_{};
    const AlphabetSimple *alphabet_ = nullptr;

public:
    explicit TinyString(const AlphabetSimple &alphabet);
    TinyString(std::vector<std::byte> data, std::size_t size, const AlphabetSimple &alphabet);
    TinyString(const TinyString &other, const AlphabetSimple &alphabet);
    TinyString(const std::string &text, const AlphabetSimple &alphabet);

    [[nodiscard]] std::string unpack() const;
    [[nodiscard]] std::size_t size() const;
    [[nodiscard]] std::vector<std::byte> shifted(uint8_t offset) const;
    [[nodiscard]] TinyString subbed(long long start, long long end) const;
    void append(const TinyString &other);

private:
    std::size_t translate_index(long long r_index) const;
};


inline TinyString::TinyString(const AlphabetSimple &alphabet) : alphabet_(&alphabet) {
}

inline TinyString::TinyString(std::vector<std::byte> data, const std::size_t size,
                              const AlphabetSimple &alphabet) : data_(std::move(data)), size_(size),
                                                                alphabet_(&alphabet) {
}

inline TinyString::TinyString(const TinyString &other, const AlphabetSimple &alphabet) : TinyString(
    std::vector<std::byte>(other.data_), other.size(), alphabet) {
}

inline TinyString::TinyString(const std::string &text, const AlphabetSimple &alphabet) : TinyString(
    alphabet.pack(text), text.size(), alphabet) {
}

inline std::string TinyString::unpack() const {
    return alphabet_->unpack(data_, size_);
}

inline std::size_t TinyString::size() const {
    return size_;
}

inline std::vector<std::byte> TinyString::shifted(const uint8_t offset) const {
    if (size_ == 0) {
        return {};
    }

    const auto out_size = static_cast<std::size_t>(
        ceil(static_cast<double>(alphabet_->get_width() * size_ + offset) / 8.0));
    std::vector<std::byte> out(out_size);

    out.at(0) = data_.at(0) << offset;
    for (std::size_t i = 1; i < data_.size(); i++) {
        out.at(i) = (data_.at(i - 1) >> (BYTE_WIDTH - offset)) | (data_.at(i) << offset);
    }
    if (out_size > data_.size()) {
        out.at(data_.size()) = data_.at(data_.size() - 1) >> (BYTE_WIDTH - offset);
    }

    return out;
}

inline TinyString TinyString::subbed(const long long start, const long long end) const {
    if (start > static_cast<long long>(size_)) {
        return {"", *alphabet_};
    }

    const std::size_t start_actual = translate_index(start);
    const std::size_t end_actual = translate_index(end);

    const std::size_t first_bit = alphabet_->get_width() * start_actual;
    // This is the first bit _not_ to be included
    //  (because it simplifies math a lot compared to having the last bit included)
    const std::size_t end_bit = alphabet_->get_width() * (end_actual + 1);
    const uint8_t first_bit_loc = first_bit % BYTE_WIDTH;
    const uint8_t end_bit_loc = end_bit % BYTE_WIDTH;
    const std::size_t first_byte = first_bit / BYTE_WIDTH;

    const auto out_size = static_cast<std::size_t>(ceil(static_cast<double>(end_bit - first_bit) / 8.0));
    std::vector<std::byte> out(out_size);

    for (std::size_t i = 0; i < out_size - 1; i++) {
        out.at(i) = data_.at(first_byte + i) >> first_bit_loc |
                    data_.at(first_byte + i + 1) << (BYTE_WIDTH - first_bit_loc);
    }

    // The logic for the last byte of the output is somewhat complex
    const std::size_t i = out_size - 1;
    if (first_bit_loc >= end_bit_loc) {
        // If the last byte spans two different bytes of the input
        //  we shift all that's left of the first byte
        //  then add the few bits of the second byte
        out.at(i) = data_.at(first_byte + i) >> first_bit_loc |
                    data_.at(first_byte + i + 1) << (BYTE_WIDTH - end_bit_loc) >> (first_bit_loc - end_bit_loc);
    } else {
        // Otherwise we shift left and right to zero everything that's outside our area of interest
        out.at(i) = data_.at(i + first_byte) << (BYTE_WIDTH - end_bit_loc) >> (BYTE_WIDTH - end_bit_loc + first_bit_loc);
    }

    return {out, end_actual - start_actual + 1, *alphabet_};
}

inline void TinyString::append(const TinyString &other) {
    if (other.size_ == 0) {
        return;
    }

    if (size_ == 0) {
        data_ = other.data_;
        size_ = other.size_;
        return;
    }

    uint8_t offset = (alphabet_->get_width() * size_) % BYTE_WIDTH;
    // If we do that then we don't have to handle special case of offset == 0 later
    offset = offset == 0 ? BYTE_WIDTH : offset;

    auto data_shifted = other.shifted(offset);

    const auto it_shifted = data_shifted.cbegin();
    data_.at(data_.size() - 1) |= *it_shifted;
    data_shifted.erase(it_shifted);

    data_.insert(data_.end(), data_shifted.cbegin(), data_shifted.cend());
    size_ += other.size_;
}

inline std::size_t TinyString::translate_index(const long long r_index) const {
    const long long size_signed = static_cast<long long>(size_);

    if (r_index > 0) {
        return std::min(r_index - 1, size_signed - 1);
    }
    if (r_index < 0) {
        return std::max(size_signed - r_index, 0ll);
    }
    cpp11::stop("0 is not a valid index");
}
