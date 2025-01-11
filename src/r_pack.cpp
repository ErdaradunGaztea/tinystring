#include <cpp11/strings.hpp>
#include <cpp11/list.hpp>
#include <cpp11/external_pointer.hpp>

#include <string>
#include <vector>
#include <algorithm>

#include "TinyStrings.h"

[[cpp11::register]]
SEXP rcpp_pack(const cpp11::strings &x, const cpp11::strings &alphabet) {
    const std::vector<std::string> std_x(x.cbegin(), x.cend());
    const std::vector<std::string> std_alphabet(alphabet.cbegin(), alphabet.cend());
    std::vector<char> char_alphabet;
    std::transform(std_alphabet.cbegin(), std_alphabet.cend(), std::back_inserter(char_alphabet),
                   [](const std::string &s) {
                       return s[0];
                   });
    auto *packed = new TinyStrings(std_x, char_alphabet);
    // ReSharper disable once CppTemplateArgumentsCanBeDeduced
    cpp11::external_pointer<TinyStrings> packed_ptr(packed);
    return packed_ptr;
}
