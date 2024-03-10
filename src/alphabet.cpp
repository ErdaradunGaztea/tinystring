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
  virtual std::string unpack(const std::vector<int>& packed) = 0;

  void recode_letter(T prev, T next) {
    auto letter_at = std::find(letters_.begin(), letters_.end(), prev);
    if (letter_at != letters_.end()) {
      *letter_at = next;
    }
  }

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
