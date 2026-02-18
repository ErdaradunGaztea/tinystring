#include <cpp11/strings.hpp>
#include <cpp11/external_pointer.hpp>

#include <string>
#include <vector>

#include <tinystring/TinyStrings.h>
#include "null_pointer.cpp"

[[cpp11::register]]
cpp11::writable::strings rcpp_unpack(SEXP x) {
    const cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    const auto unpacked = x_ptr->unpack();

    cpp11::writable::strings ret(
        unpacked.cbegin(),
        unpacked.cend()
    );

    return ret;
}
