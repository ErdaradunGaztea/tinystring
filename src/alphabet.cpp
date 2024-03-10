#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

class Alphabet {
  std::vector<std::string> letters_;
  uint8_t size_;

public:
  Alphabet(std::vector<std::string> letters) : letters_(letters) {
    size_ = determine_size(letters);
  }

  std::vector<int> pack(std::string string) {
    // TODO: actually pack
    std::vector<int> ret;
    std::transform(string.cbegin(), string.cend(), std::back_inserter(ret), [this](char s) {
      int index = 0;
      bool found = false;
      for (auto letter : letters_) {
        if (s == letter[0]) {
          found = true;
          break;
        }
        index++;
      }
      if (!found) {
        index = pow(2, size_) - 1;
      }
      return index;
    });
    return ret;
  }

private:
  uint8_t determine_size(const std::vector<std::string>& letters) {
    return std::ceil(std::log2(letters.size() + 1));
  }

public:
  uint8_t get_size() {
    return size_;
  }
};
