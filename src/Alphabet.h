#pragma once
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
  virtual ~Alphabet() = default;
  explicit Alphabet(std::vector<T> letters);

  // Packing algorithm differs between simple and complex alphabets
  [[nodiscard]] virtual std::vector<int> pack(const std::string& string) const = 0;
  [[nodiscard]] virtual std::string unpack(const std::vector<int>& packed) const = 0;

  void recode_letter(T prev, T next);
  [[nodiscard]] uint8_t get_width() const;

private:
  uint8_t determine_width(const std::vector<T>& letters);
};


template<class T>
Alphabet<T>::Alphabet(std::vector<T> letters) : letters_(letters) {
  width_ = determine_width(letters);
}

template<class T>
void Alphabet<T>::recode_letter(T prev, T next) {
  auto letter_at = std::find(letters_.begin(), letters_.end(), prev);
  if (letter_at != letters_.end()) {
    *letter_at = next;
  }
}

template<class T>
uint8_t Alphabet<T>::get_width() const {
  return width_;
}

template<class T>
uint8_t Alphabet<T>::determine_width(const std::vector<T>& letters) {
  return std::ceil(std::log2(letters.size() + 1));
}
