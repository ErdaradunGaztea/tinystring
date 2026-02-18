#include <cpp11/external_pointer.hpp>
#include <cpp11/strings.hpp>

#include <tinystring/TinyStrings.h>
#include "null_pointer.cpp"

[[cpp11::register]]
SEXP rcpp_alphabet(SEXP x) {
    const cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    const auto &letters = x_ptr->get_alphabet().get_letters();

    cpp11::writable::strings ret;
    ret.reserve(static_cast<R_xlen_t>(letters.size()));

    for (const auto &letter: letters) {
        ret.push_back(std::string(1, letter));
    }

    return ret;
}
