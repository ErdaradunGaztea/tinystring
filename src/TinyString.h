#pragma once

#include <vector>

#include "AlphabetSimple.h"


class TinyString {
    std::vector<std::byte> data_{};
    size_t size_{};
    const AlphabetSimple *alphabet_ = nullptr;

public:
    template<bool CONST>
    class Iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::byte;
        using pointer = std::conditional_t<CONST, const std::byte*, std::byte*>;
        using reference = std::conditional_t<CONST, const std::byte&, std::byte&>;
        using data_type = std::conditional_t<CONST, const std::vector<std::byte>, std::vector<std::byte>>;

    protected:
        data_type data_;
        size_t position_;

    public:
        explicit Iterator(const std::vector<std::byte>& data, size_t position);

        reference operator*();
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    typedef Iterator<true> const_iterator;
    typedef Iterator<false> iterator;

    explicit TinyString(const AlphabetSimple &alphabet);
    TinyString(const TinyString &other, const AlphabetSimple &alphabet);
    TinyString(const std::string &text, const AlphabetSimple &alphabet);

    [[nodiscard]] std::string unpack() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] iterator begin() const;
    [[nodiscard]] iterator end() const;
    [[nodiscard]] const_iterator cbegin() const;
    [[nodiscard]] const_iterator cend() const;
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

inline TinyString::iterator TinyString::begin() const {
    return iterator(data_, 0);
}

inline TinyString::iterator TinyString::end() const {
    return iterator(data_, size_);
}

inline TinyString::const_iterator TinyString::cbegin() const {
    return const_iterator(data_, 0);
}

inline TinyString::const_iterator TinyString::cend() const {
    return const_iterator(data_, size_);
}

inline std::vector<std::byte> TinyString::shifted(const size_t offset) const {
    constexpr uint8_t BYTE_WIDTH = 8u;

    if (size_ == 0) {
        return std::vector<std::byte>();
    }

    const size_t out_size = ceil((alphabet_->get_width() * size_ + offset) / 8.0);
    std::vector<std::byte> out(out_size);

    out[0] = data_[0] << offset;
    for (size_t i = 1; i < size_; i++) {
        out[i] = (data_[i - 1] >> (BYTE_WIDTH - offset)) | (data_[i] << offset);
    }
    if (out_size > size_) {
        out[size_] = data_[size_] >> (BYTE_WIDTH - offset);
    }

    return out;
}

inline void TinyString::append(const TinyString &other) {
    size_ += other.size_;
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
};

// Iterator -----------------------------------------------------------------------------------------------------------
template<bool CONST>
TinyString::Iterator<CONST>::Iterator(const std::vector<std::byte> &data, const size_t position) : data_(data), position_(position) {
}

template<bool CONST>
typename TinyString::Iterator<CONST>::reference TinyString::Iterator<CONST>::operator*() {
    return data_[position_];
}

template<bool CONST>
TinyString::Iterator<CONST>& TinyString::Iterator<CONST>::operator++() {
    ++position_;
    return *this;
}

template<bool CONST>
TinyString::Iterator<CONST> TinyString::Iterator<CONST>::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<bool CONST>
bool TinyString::Iterator<CONST>::operator==(const Iterator& other) const {
    return position_ == other.position_;
}

template<bool CONST>
bool TinyString::Iterator<CONST>::operator!=(const Iterator& other) const {
    return !(*this == other);
}
