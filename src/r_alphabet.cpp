#include <cpp11/external_pointer.hpp>
#include <cpp11/strings.hpp>

#include <tinystring/TinyStrings.h>
#include <tinystring_types.h>
#include "null_pointer.cpp"

[[cpp11::register]]
cpp11::writable::strings rcpp_alphabet(const TinyStrings_ptr& x_ptr) {
    assert_not_null_pointer(x_ptr);

    const auto &letters = x_ptr->get_alphabet().get_letters();

    cpp11::writable::strings ret;
    ret.reserve(static_cast<R_xlen_t>(letters.size()));

    for (const auto &letter: letters) {
        ret.push_back(std::string(1, letter));
    }

    return ret;
}
