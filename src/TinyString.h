#pragma once

#include <vector>

#include "AlphabetSimple.h"


class TinyString {
    std::vector<std::byte> data_{};
    size_t size_{};
    const AlphabetSimple *alphabet_ = nullptr;

public:
    explicit TinyString(const AlphabetSimple &alphabet);
    TinyString(std::vector<std::byte> data, size_t size, const AlphabetSimple &alphabet);
    TinyString(const TinyString &other, const AlphabetSimple &alphabet);
    TinyString(const std::string &text, const AlphabetSimple &alphabet);

    [[nodiscard]] std::string unpack() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] std::vector<std::byte> shifted(size_t offset) const;
    TinyString subbed(size_t start, size_t end) const;
    void append(const TinyString &other);
};


inline TinyString::TinyString(const AlphabetSimple &alphabet) : alphabet_(&alphabet) {
}

inline TinyString::TinyString(std::vector<std::byte> data, const size_t size,
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

inline size_t TinyString::size() const {
    return size_;
}

inline std::vector<std::byte> TinyString::shifted(const size_t offset) const {
    constexpr uint8_t BYTE_WIDTH = 8u;

    if (size_ == 0) {
        return {};
    }

    const auto out_size = static_cast<size_t>(
        ceil(static_cast<double>(alphabet_->get_width() * size_ + offset) / 8.0));
    std::vector<std::byte> out(out_size);

    out.at(0) = data_.at(0) << offset;
    for (size_t i = 1; i < data_.size(); i++) {
        out.at(i) = (data_.at(i - 1) >> (BYTE_WIDTH - offset)) | (data_.at(i) << offset);
    }
    if (out_size > data_.size()) {
        out.at(data_.size()) = data_.at(data_.size() - 1) >> (BYTE_WIDTH - offset);
    }

    return out;
}

inline TinyString TinyString::subbed(const size_t start, const size_t end) const {
    constexpr uint8_t BYTE_WIDTH = 8u;

    const size_t first_bit = alphabet_->get_width() * start;
    // This is the first bit _not_ to be included
    //  (because it simplifies math a lot compared to having the last bit included)
    const size_t end_bit = alphabet_->get_width() * (end + 1);
    const uint8_t first_bit_loc = first_bit % BYTE_WIDTH;
    const uint8_t end_bit_loc = end_bit % BYTE_WIDTH;
    const size_t first_byte = first_bit / BYTE_WIDTH;

    const auto out_size = static_cast<size_t>(ceil(static_cast<double>(end_bit - first_bit) / 8.0));
    std::vector<std::byte> out(out_size);

    for (size_t i = 0; i < out_size - 1; i++) {
        out.at(i) = data_.at(first_byte + i) >> first_bit_loc |
                    data_.at(first_byte + i + 1) << (8 - first_bit_loc);
    }

    // The logic for the last byte of the output is somewhat complex
    const size_t i = out_size - 1;
    if (first_bit_loc >= end_bit_loc) {
        // If the last byte spans two different bytes of the input
        //  we shift all that's left of the first byte
        //  then add the few bits of the second byte
        out.at(i) = data_.at(first_byte + i) >> first_bit_loc |
                    data_.at(first_byte + i + 1) << (8 - end_bit_loc) >> (first_bit_loc - end_bit_loc);
    } else {
        // Otherwise we shift left and right to zero everything that's outside our area of interest
        out.at(i) = data_.at(i + first_byte) << (8 - end_bit_loc) >> (8 - end_bit_loc + first_bit_loc);
    }

    return TinyString(out, end - start + 1, *alphabet_);
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

    uint8_t offset = (alphabet_->get_width() * size_) % 8;
    // If we do that then we don't have to handle special case of offset == 0 later
    offset = offset == 0 ? 8 : offset;

    auto data_shifted = other.shifted(offset);

    const auto it_shifted = data_shifted.cbegin();
    data_.at(data_.size() - 1) |= *it_shifted;
    data_shifted.erase(it_shifted);

    data_.insert(data_.end(), data_shifted.cbegin(), data_shifted.cend());
    size_ += other.size_;
}
