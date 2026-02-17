#pragma once

#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>

#include "AlphabetSimple.h"
#include "TinyString.h"


class TinyStrings {
    std::vector<TinyString> data_;
    AlphabetSimple alphabet_;

public:
    TinyStrings(const std::vector<std::string> &strings, AlphabetSimple alphabet);
    TinyStrings(const std::vector<std::string> &strings, const std::vector<char> &letters);
    TinyStrings(const TinyStrings &other);

    [[nodiscard]] std::vector<std::string> unpack() const;
    [[nodiscard]] TinyStrings *flattened(const std::vector<std::string>& collapse) const;
    [[nodiscard]] TinyStrings *subbed(long long start, long long end) const;
    [[nodiscard]] std::vector<std::size_t> sizes() const;
    std::vector<TinyString> &get_data();
    AlphabetSimple &get_alphabet();

private:
    TinyStrings(const std::vector<TinyString> &data, AlphabetSimple alphabet);
    TinyStrings(const TinyString &scalar_data, AlphabetSimple alphabet);
};


inline TinyStrings::TinyStrings(const std::vector<std::string> &strings, AlphabetSimple alphabet) : alphabet_(
    std::move(alphabet)) {
    std::transform(strings.cbegin(), strings.cend(), std::back_inserter(data_), [this](const std::string &s) {
        return TinyString(s, alphabet_);
    });
}

inline TinyStrings::TinyStrings(const std::vector<std::string> &strings,
                                const std::vector<char> &letters) : TinyStrings(strings, AlphabetSimple(letters)) {
}

inline TinyStrings::TinyStrings(const TinyStrings &other) : alphabet_(other.alphabet_) {
    std::transform(other.data_.cbegin(), other.data_.cend(), std::back_inserter(data_), [this](const TinyString &s) {
       return TinyString(s, alphabet_);
    });
}

inline std::vector<std::string> TinyStrings::unpack() const {
    std::vector<std::string> ret;
    std::transform(data_.cbegin(), data_.cend(), std::back_inserter(ret), [](const TinyString &s) {
        return s.unpack();
    });
    return ret;
}

inline TinyStrings* TinyStrings::flattened(const std::vector<std::string>& collapse) const {
    const TinyString collapse_tstr(collapse, alphabet_);

    TinyString flat_data(alphabet_);

    bool first = true;
    for (const auto &s: data_) {
        // Prepend collapse separator before every string but the first
        if (!std::exchange(first, false)) {
            flat_data.append(collapse_tstr);
        }
        flat_data.append(s);
    }

    return new TinyStrings(flat_data, alphabet_);
}

inline TinyStrings* TinyStrings::subbed(const long long start, const long long end) const {
    std::vector<TinyString> subbed{};
    std::transform(data_.cbegin(), data_.cend(), std::back_inserter(subbed), [start, end](const TinyString &s) {
        return s.subbed(start, end);
    });
    return new TinyStrings(subbed, alphabet_);
}

inline std::vector<std::size_t> TinyStrings::sizes() const {
    std::vector<std::size_t> ret;
    // Extracting .size() would be easier in C++20, where we'd have access to std::ranges
    std::transform(data_.cbegin(), data_.cend(), std::back_inserter(ret), [](const TinyString &s) {
        return s.size();
    });
    return ret;
}

inline std::vector<TinyString> &TinyStrings::get_data() {
    return data_;
}

inline AlphabetSimple &TinyStrings::get_alphabet() {
    return alphabet_;
}

inline TinyStrings::TinyStrings(const std::vector<TinyString> &data, AlphabetSimple alphabet) : data_(data),
    alphabet_(std::move(alphabet)) {
}

inline TinyStrings::TinyStrings(const TinyString &scalar_data, AlphabetSimple alphabet) : alphabet_(
    std::move(alphabet)) {
    data_.push_back(scalar_data);
}
