#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <stdexcept>

#include "Alphabet.h"


class AlphabetSimple final : public Alphabet<char> {
public:
    explicit AlphabetSimple(const std::vector<char> &letters);

    [[nodiscard]] std::vector<std::byte> pack(const std::string &text) const override;
    [[nodiscard]] std::string unpack(const std::vector<std::byte> &packed, size_t size) const override;
    [[nodiscard]] std::byte match_index(char letter) const override;
    [[nodiscard]] char match_letter(std::byte index) const;

private:
    template<uint8_t WIDTH>
    [[nodiscard]] std::vector<std::byte> pack(const std::string &text) const;
    template<uint8_t WIDTH>
    std::string unpack(const std::vector<std::byte> &packed, size_t size) const;
};


// ReSharper disable once CppRedundantTemplateArguments
inline AlphabetSimple::AlphabetSimple(const std::vector<char> &letters) : Alphabet<char>(letters) {
}

inline std::vector<std::byte> AlphabetSimple::pack(const std::string &text) const {
    switch (get_width()) {
        case 2:
            return pack<2>(text);
        case 3:
            return pack<3>(text);
        case 4:
            return pack<4>(text);
        case 5:
            return pack<5>(text);
        case 6:
            return pack<6>(text);
        case 7:
            return pack<7>(text);
        case 8:
            return pack<8>(text);
        default:
            throw std::invalid_argument(std::string("\"alphabet\" has invalid alphabet size - it's ") +
                                          std::to_string(get_width()) +
                                          " but should be between 2 and 8 inclusive");
    }
}

inline std::string AlphabetSimple::unpack(const std::vector<std::byte> &packed, size_t size) const {
    switch (get_width()) {
        case 2:
            return unpack<2>(packed, size);
        case 3:
            return unpack<3>(packed, size);
        case 4:
            return unpack<4>(packed, size);
        case 5:
            return unpack<5>(packed, size);
        case 6:
            return unpack<6>(packed, size);
        case 7:
            return unpack<7>(packed, size);
        case 8:
            return unpack<8>(packed, size);
        default:
            throw std::invalid_argument(std::string("\"alphabet\" has invalid alphabet size - it's ") +
                                          std::to_string(get_width()) +
                                          " but should be between 2 and 8 inclusive");
    }
}

inline std::byte AlphabetSimple::match_index(const char letter) const {
    const auto result = std::find(letters_.cbegin(), letters_.cend(), letter);
    return result != letters_.cend() ? static_cast<std::byte>(std::distance(letters_.cbegin(), result)) : max_index_;
}

inline char AlphabetSimple::match_letter(const std::byte index) const {
    return index == max_index_ ? '!' : letters_.at(static_cast<int>(index));
}

template<uint8_t WIDTH>
std::vector<std::byte> AlphabetSimple::pack(const std::string& text) const {
    // ReSharper disable once CppTooWideScope
    constexpr uint8_t BYTE_WIDTH = 8u;
    const std::vector<std::byte>::size_type out_size = ceil(static_cast<double>(text.size()) * WIDTH / 8.0);
    std::vector<std::byte> out(out_size);

    std::vector<std::byte>::size_type out_byte = 0;
    uint8_t shift = 0u;

    for (const auto letter : text) {
        const auto packed_letter = match_index(letter);
        out[out_byte] |= packed_letter << shift;
        // If shift + length exceeds 1 byte width, we need to fit the rest of the packed letter in the next byte
        if (shift > BYTE_WIDTH - WIDTH) {
            out[out_byte + 1] |= (packed_letter >> (BYTE_WIDTH - shift));
        }

        shift += WIDTH;
        if (shift >= BYTE_WIDTH) {
            shift -= BYTE_WIDTH;
            out_byte++;
        }
    }

    return out;
}

template<uint8_t WIDTH>
std::string AlphabetSimple::unpack(const std::vector<std::byte> &packed, const size_t size) const {
    constexpr uint8_t BYTE_WIDTH = 8u;
    std::string out;
    out.reserve(size);

    std::vector<std::byte>::size_type out_byte = 0;
    uint8_t shift = BYTE_WIDTH - WIDTH;

    // The solution here is in many ways the reverse of pack()
    for (size_t i = 0; i < size; i++) {
        std::byte index = packed[out_byte] << shift >> BYTE_WIDTH - WIDTH;
        // Since we optionally included the next byte in pack(), here we include the previous byte instead
        if (shift > BYTE_WIDTH - WIDTH) {
            index |= packed[out_byte - 1] >> 2 * BYTE_WIDTH - WIDTH - shift;
        }
        out += match_letter(index);

        // Previously we were adding to shift modulo 8, now we're subtracting
        if (shift < WIDTH) {
            shift += BYTE_WIDTH;
            out_byte++;
        }
        shift -= WIDTH;
    }

    return out;
}
