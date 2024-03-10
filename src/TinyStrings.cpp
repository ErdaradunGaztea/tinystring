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

  std::vector<std::vector<int>> get_data() {
    return data_;
  }
};
