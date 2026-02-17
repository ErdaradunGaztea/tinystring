#include <cpp11/external_pointer.hpp>
#include <cpp11/strings.hpp>

#include <tinystring/TinyStrings.h>
#include "null_pointer.cpp"

[[cpp11::register]]
SEXP rcpp_flatten(SEXP x, const cpp11::strings &collapse) {
    const cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    const std::vector<std::string> std_collapse(collapse.cbegin(), collapse.cend());

    TinyStrings *flattened = x_ptr->flattened(std_collapse);
    cpp11::external_pointer<TinyStrings> flattened_ptr(flattened);

    return flattened_ptr;
}
