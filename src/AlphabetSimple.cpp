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
    int max_index = pow(2, width_) - 1;
    std::transform(string.cbegin(), string.cend(), std::back_inserter(ret), [this, max_index](char s) {
      auto result = std::find(letters_.cbegin(), letters_.cend(), s);
      return result != letters_.cend() ? std::distance(letters_.cbegin(), result) : max_index;
    });
    return ret;
  }

  std::string unpack(const std::vector<int>& packed) {
    std::vector<char> unpacked;
    int max_index = pow(2, width_) - 1;
    std::transform(packed.cbegin(), packed.cend(), std::back_inserter(unpacked), [this, max_index](int index) {
      // TODO: do not hardcode missing letter
      return index == max_index ? '!' : letters_.at(index);
    });
    std::string ret(unpacked.cbegin(), unpacked.cend());
    return ret;
  }
};
