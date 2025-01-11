#pragma once
#include <vector>

#include "AlphabetSimple.h"


class TinyString {
    std::vector<int> data_{};
    size_t size_{};
    const AlphabetSimple *alphabet_ = nullptr;

public:
    class Iterator {
        std::vector<int> data_;
        size_t position_;

    public:
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = int*;
        using reference = int&;

        explicit Iterator(const std::vector<int>& data, size_t position);

        reference operator*();
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    class ConstIterator {
        std::vector<int> data_;
        size_t position_;

    public:
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = const int*;
        using reference = const int&;

        explicit ConstIterator(const std::vector<int>& data, size_t position);

        reference operator*() const;
        ConstIterator& operator++();
        ConstIterator operator++(int);
        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;
    };

    explicit TinyString(const AlphabetSimple &alphabet);
    TinyString(const TinyString &other, const AlphabetSimple &alphabet);
    TinyString(const std::string &text, const AlphabetSimple &alphabet);

    [[nodiscard]] std::string unpack() const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] Iterator begin() const;
    [[nodiscard]] Iterator end() const;
    [[nodiscard]] ConstIterator cbegin() const;
    [[nodiscard]] ConstIterator cend() const;
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
    return alphabet_->unpack(data_);
}

inline size_t TinyString::size() const {
    return size_;
}

inline TinyString::Iterator TinyString::begin() const {
    return Iterator(data_, 0);
}

inline TinyString::Iterator TinyString::end() const {
    return Iterator(data_, size_);
}

inline TinyString::ConstIterator TinyString::cbegin() const {
    return ConstIterator(data_, 0);
}

inline TinyString::ConstIterator TinyString::cend() const {
    return ConstIterator(data_, size_);
}

inline void TinyString::append(const TinyString &other) {
    size_ += other.size_;
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
};

// Iterator -----------------------------------------------------------------------------------------------------------
inline TinyString::Iterator::Iterator(const std::vector<int> &data, const size_t position) : data_(data), position_(position) {
}

inline TinyString::Iterator::reference TinyString::Iterator::operator*() {
    return data_[position_];
}

inline TinyString::Iterator& TinyString::Iterator::operator++() {
    ++position_;
    return *this;
}

inline TinyString::Iterator TinyString::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

inline bool TinyString::Iterator::operator==(const Iterator& other) const {
    return position_ == other.position_;
}

inline bool TinyString::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

// ConstIterator ------------------------------------------------------------------------------------------------------
inline TinyString::ConstIterator::ConstIterator(const std::vector<int> &data, const size_t position) : data_(data), position_(position) {
}

inline TinyString::ConstIterator::reference TinyString::ConstIterator::operator*() const {
    return data_[position_];
}

inline TinyString::ConstIterator& TinyString::ConstIterator::operator++() {
    ++position_;
    return *this;
}

inline TinyString::ConstIterator TinyString::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

inline bool TinyString::ConstIterator::operator==(const ConstIterator& other) const {
    return position_ == other.position_;
}

inline bool TinyString::ConstIterator::operator!=(const ConstIterator& other) const {
    return !(*this == other);
}
