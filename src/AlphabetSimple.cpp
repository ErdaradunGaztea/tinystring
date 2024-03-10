#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

class AlphabetSimple {
  std::vector<char> letters_;
  uint8_t width_;

public:
  AlphabetSimple(std::vector<char> letters) : letters_(letters) {
    width_ = determine_width(letters);
  }

  std::vector<int> pack(const std::string& string) {
    // TODO: actually pack
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

private:
  uint8_t determine_width(const std::vector<char>& letters) {
    return std::ceil(std::log2(letters.size() + 1));
  }

public:
  uint8_t get_width() {
    return width_;
  }
};
