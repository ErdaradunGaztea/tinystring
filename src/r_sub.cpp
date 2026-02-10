#include <cpp11/external_pointer.hpp>
#include <cpp11/integers.hpp>

#include <tinystring/TinyStrings.h>
#include "null_pointer.cpp"

[[cpp11::register]]
SEXP rcpp_sub(SEXP x, const long long start, const long long end) {
    const cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    TinyStrings *subbed = x_ptr->subbed(start, end);
    cpp11::external_pointer<TinyStrings> subbed_ptr(subbed);

    return subbed_ptr;
}
