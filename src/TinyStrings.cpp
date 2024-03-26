#include <vector>
#include <algorithm>

#include "AlphabetSimple.cpp"

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

  std::vector<std::string> unpack() {
    std::vector<std::string> ret;
    std::transform(data_.cbegin(), data_.cend(), std::back_inserter(ret), [this](std::vector<int> s) {
      return alphabet_.unpack(s);
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
