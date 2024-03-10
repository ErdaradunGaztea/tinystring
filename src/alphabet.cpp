#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

template<class T>
class Alphabet {
protected:
  std::vector<T> letters_;
  uint8_t width_;

public:
  Alphabet(std::vector<T> letters) : letters_(letters) {
    width_ = determine_width(letters);
  }

  // Packing algorithm differs between simple and complex alphabets
  virtual std::vector<int> pack(const std::string& string) = 0;

private:
  uint8_t determine_width(const std::vector<T>& letters) {
    return std::ceil(std::log2(letters.size() + 1));
  }

public:
  // TODO: remove unless necessary
  uint8_t get_width() {
    return width_;
  }
};
