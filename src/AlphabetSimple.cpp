#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

#include "Alphabet.cpp"

class AlphabetSimple : public Alphabet<char> {
public:
  AlphabetSimple(std::vector<char> letters) : Alphabet<char>(letters) {}

  std::vector<int> pack(const std::string& string) {
    // TODO: pack instead of simply indexing
    std::vector<int> ret;
    std::transform(string.cbegin(), string.cend(), std::back_inserter(ret), [this](char s) {
      int index = pow(2, width_) - 1;
      auto result = std::find(letters_.cbegin(), letters_.cend(), s);
      if (result != letters_.cend()) {
        index = std::distance(letters_.cbegin(), result);
      }
      return index;
    });
    return ret;
  }
};
