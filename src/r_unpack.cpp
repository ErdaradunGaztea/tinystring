#include <cpp11/strings.hpp>
#include <cpp11/external_pointer.hpp>

#include <vector>

#include <tinystring/TinyStrings.h>
#include <tinystring_types.h>
#include "null_pointer.cpp"

[[cpp11::register]]
cpp11::writable::strings rcpp_unpack(const TinyStrings_ptr& x_ptr) {
    assert_not_null_pointer(x_ptr);

    const auto unpacked = x_ptr->unpack();

    cpp11::writable::strings ret(
        unpacked.cbegin(),
        unpacked.cend()
    );

    return ret;
}
