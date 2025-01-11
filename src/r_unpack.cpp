#include <cpp11/strings.hpp>
#include <cpp11/external_pointer.hpp>

#include <string>
#include <vector>

#include "TinyStrings.h"
#include "null_pointer.cpp"

[[cpp11::register]]
cpp11::strings rcpp_unpack(SEXP x) {
    const cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);
    auto unpacked = x_ptr->unpack();
    cpp11::writable::strings ret;
    for (const auto &sequence: unpacked) {
        ret.push_back(sequence);
    }
    return static_cast<cpp11::r_vector<cpp11::r_string>>(ret);
}
