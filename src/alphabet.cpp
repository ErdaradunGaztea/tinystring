#include <cmath>
#include <string>
#include <vector>

#include <iostream>
#include <fstream>

class Alphabet {
  std::vector<std::string> letters_;
  uint8_t size_;

public:
  Alphabet(std::vector<std::string> letters) : letters_(letters) {
    size_ = determine_size(letters);
    printf("Created alphabet with size %i", size_);
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
