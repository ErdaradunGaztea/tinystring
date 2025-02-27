#pragma once

#include <vector>

#include "AlphabetSimple.h"


class TinyString {
    std::vector<std::byte> data_{};
    size_t size_{};
    const AlphabetSimple *alphabet_ = nullptr;

public:
    explicit TinyString(const AlphabetSimple &alphabet);
    TinyString(const TinyString &other, const AlphabetSimple &alphabet);
    TinyString(const std::string &text, const AlphabetSimple &alphabet);

    [[nodiscard]] std::string unpack() const;
    [[nodiscard]] size_t size() const;
    std::vector<std::byte> shifted(size_t offset) const;
    void append(const TinyString &other);
};


inline TinyString::TinyString(const AlphabetSimple &alphabet) : alphabet_(&alphabet) {
}

inline TinyString::TinyString(const TinyString &other, const AlphabetSimple &alphabet) : alphabet_(&alphabet) {
    size_ = other.size();
    data_ = other.data_;
}

inline TinyString::TinyString(const std::string &text, const AlphabetSimple &alphabet) : alphabet_(&alphabet) {
    size_ = text.size();
    data_ = alphabet.pack(text);
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
        return std::vector<std::byte>();
    }

    const size_t out_size = static_cast<size_t>(
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
