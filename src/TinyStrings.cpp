#include <vector>
#include <algorithm>

#include "Alphabet.cpp"

class TinyStrings {
  std::vector<std::vector<int>> data_;
  Alphabet alphabet_;

public:
  TinyStrings(std::vector<std::string> strings, Alphabet alphabet) : alphabet_(alphabet) {
    std::transform(strings.cbegin(), strings.cend(), std::back_inserter(data_), [this](std::string s) {
      return alphabet_.pack(s);
    });
  }

  TinyStrings(std::vector<std::string> strings, std::vector<std::string> letters) : TinyStrings(strings, Alphabet(letters)) {}

  std::vector<std::vector<int>> get_data() {
    return data_;
  }
};
