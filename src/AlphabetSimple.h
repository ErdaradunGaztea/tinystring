#pragma once
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

#include "Alphabet.h"


class AlphabetSimple final : public Alphabet<char> {
public:
    explicit AlphabetSimple(const std::vector<char> &letters);

    [[nodiscard]] std::vector<int> pack(const std::string &string) const override;

    [[nodiscard]] std::string unpack(const std::vector<int> &packed) const override;
};


inline AlphabetSimple::AlphabetSimple(const std::vector<char> &letters) : Alphabet<char>(letters) {
};

inline std::vector<int> AlphabetSimple::pack(const std::string &string) const {
    // TODO: pack instead of simply indexing
    std::vector<int> ret;
    int max_index = static_cast<int>(pow(2, width_)) - 1;
    std::transform(string.cbegin(), string.cend(), std::back_inserter(ret), [this, max_index](const char s) {
        const auto result = std::find(letters_.cbegin(), letters_.cend(), s);
        return result != letters_.cend() ? std::distance(letters_.cbegin(), result) : max_index;
    });
    return ret;
}

inline std::string AlphabetSimple::unpack(const std::vector<int> &packed) const {
    std::vector<char> unpacked;
    int max_index = static_cast<int>(pow(2, width_)) - 1;
    std::transform(packed.cbegin(), packed.cend(), std::back_inserter(unpacked), [this, max_index](const int index) {
        // TODO: do not hardcode missing letter
        return index == max_index ? '!' : letters_.at(index);
    });
    std::string ret(unpacked.cbegin(), unpacked.cend());
    return ret;
}
