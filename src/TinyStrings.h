#include <cmath>
#include <vector>
#include <algorithm>

#include "AlphabetSimple.h"

class TinyStrings {
  std::vector<std::vector<int>> data_;
  AlphabetSimple alphabet_;

public:
  TinyStrings(std::vector<std::string> strings, AlphabetSimple alphabet) : alphabet_(alphabet) {
    std::transform(strings.cbegin(), strings.cend(), std::back_inserter(data_), [this](std::string s) {
      return alphabet_.pack(s);
    });
  }

  TinyStrings(std::vector<std::string> strings, std::vector<char> letters) : TinyStrings(strings, AlphabetSimple(letters)) {}

private:
  TinyStrings(std::vector<std::vector<int>> data, AlphabetSimple alphabet) : data_(data), alphabet_(alphabet) {}

  TinyStrings(std::vector<int> scalar_data, AlphabetSimple alphabet) : alphabet_(alphabet) {
    data_.push_back(scalar_data);
  }

public:
  std::vector<std::string> unpack() {
    std::vector<std::string> ret;
    std::transform(data_.cbegin(), data_.cend(), std::back_inserter(ret), [this](std::vector<int> s) {
      return alphabet_.unpack(s);
    });
    return ret;
  }

  TinyStrings* flattened() {
    std::size_t total_size = 0;
    for (auto s : data_) {
      total_size += s.size();
    }

    std::vector<int> flat_data;
    flat_data.reserve(total_size);

    for (auto s : data_) {
      flat_data.insert(flat_data.end(), s.cbegin(), s.cend());
    }

    auto flattened = new TinyStrings(flat_data, alphabet_);
    return flattened;
  }

  std::vector<std::vector<int>::size_type> sizes() {
    std::vector<std::vector<int>::size_type> ret;
    std::transform(data_.cbegin(), data_.cend(), std::back_inserter(ret), [this](std::vector<int> s) {
      return std::ceil(s.size() * alphabet_.get_width() / 8.0);
    });
    return ret;
  }

  std::vector<std::vector<int>>& get_data() {
    return data_;
  }

  AlphabetSimple& get_alphabet() {
    return alphabet_;
  }
};
