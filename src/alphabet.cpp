#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

class Alphabet {
  std::vector<std::string> letters_;
  uint8_t width_;

public:
  Alphabet(std::vector<std::string> letters) : letters_(letters) {
    width_ = determine_width(letters);
  }

private:
  uint8_t determine_width(const std::vector<std::string>& letters) {
    return std::ceil(std::log2(letters.size() + 1));
  }

public:
  uint8_t get_width() {
    return width_;
  }
};
