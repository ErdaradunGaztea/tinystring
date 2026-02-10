#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <algorithm>


template<class T>
class Alphabet {
protected:
    std::vector<T> letters_;
    const uint8_t width_;
    const std::byte max_index_;

public:
    virtual ~Alphabet() = default;
    explicit Alphabet(std::vector<T> letters);

    // Packing algorithm differs between simple and complex alphabets
    [[nodiscard]] virtual std::vector<std::byte> pack(const std::string &text) const = 0;
    [[nodiscard]] virtual std::string unpack(const std::vector<std::byte> &packed, std::size_t size) const = 0;
    // Returning `char` here limits us to 8-bit alphabets
    virtual std::byte match_index(T letter) const = 0;
    void recode_letter(T prev, T next);
    [[nodiscard]] uint8_t get_width() const;

private:
    static uint8_t determine_width(const std::vector<T> &letters);
    static std::byte max_index(const std::vector<T> &letters);
};


template<class T>
Alphabet<T>::Alphabet(std::vector<T> letters) : letters_(letters), width_(determine_width(letters)),
                                                max_index_(max_index(letters)) {
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
uint8_t Alphabet<T>::determine_width(const std::vector<T> &letters) {
    return std::ceil(std::log2(letters.size() + 1));
}

template<class T>
std::byte Alphabet<T>::max_index(const std::vector<T> &letters) {
    return static_cast<std::byte>(pow(2, determine_width(letters)) - 1);
}
