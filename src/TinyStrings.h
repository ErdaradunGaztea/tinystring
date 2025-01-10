#pragma once
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>

#include "AlphabetSimple.h"


class TinyStrings {
  std::vector<std::vector<int>> data_;
  AlphabetSimple alphabet_;

public:
  TinyStrings(const std::vector<std::string>& strings, AlphabetSimple alphabet);
  TinyStrings(const std::vector<std::string>& strings, const std::vector<char>& letters);
  TinyStrings(const TinyStrings& other) = default;

  [[nodiscard]] std::vector<std::string> unpack() const;
  [[nodiscard]] TinyStrings* flattened() const;
  [[nodiscard]] std::vector<std::vector<int>::size_type> sizes() const;

  std::vector<std::vector<int>>& get_data();
  AlphabetSimple& get_alphabet();

private:
  TinyStrings(const std::vector<std::vector<int>> &data, AlphabetSimple alphabet);
  TinyStrings(const std::vector<int> &scalar_data, AlphabetSimple alphabet);
};


inline TinyStrings::TinyStrings(const std::vector<std::string>& strings, AlphabetSimple alphabet) : alphabet_(std::move(alphabet)) {
  std::transform(strings.cbegin(), strings.cend(), std::back_inserter(data_), [this](const std::string& s) {
    return alphabet_.pack(s);
  });
}

inline TinyStrings::TinyStrings(const std::vector<std::string>& strings, const std::vector<char>& letters) : TinyStrings(strings, AlphabetSimple(letters)) {}

inline std::vector<std::string> TinyStrings::unpack() const {
  std::vector<std::string> ret;
  std::transform(data_.cbegin(), data_.cend(), std::back_inserter(ret), [this](const std::vector<int>& s) {
    return alphabet_.unpack(s);
  });
  return ret;
}

inline TinyStrings* TinyStrings::flattened() const {
  std::size_t total_size = 0;
  for (const auto& s : data_) {
    total_size += s.size();
  }

  std::vector<int> flat_data;
  flat_data.reserve(total_size);

  for (const auto& s : data_) {
    flat_data.insert(flat_data.end(), s.cbegin(), s.cend());
  }

  const auto flattened = new TinyStrings(flat_data, alphabet_);
  return flattened;
}

inline std::vector<std::vector<int>::size_type> TinyStrings::sizes() const {
  std::vector<std::vector<int>::size_type> ret;
  std::transform(data_.cbegin(), data_.cend(), std::back_inserter(ret), [this](const std::vector<int>& s) {
    return std::ceil(static_cast<double>(s.size()) * alphabet_.get_width() / 8.0);
  });
  return ret;
}

inline std::vector<std::vector<int>>& TinyStrings::get_data() {
  return data_;
}

inline AlphabetSimple& TinyStrings::get_alphabet() {
  return alphabet_;
}

inline TinyStrings::TinyStrings(const std::vector<std::vector<int>> &data, AlphabetSimple alphabet) : data_(data), alphabet_(std::move(alphabet)) {}

inline TinyStrings::TinyStrings(const std::vector<int> &scalar_data, AlphabetSimple alphabet) : alphabet_(std::move(alphabet)) {
  data_.push_back(scalar_data);
}
