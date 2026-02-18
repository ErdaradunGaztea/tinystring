#include <cpp11/external_pointer.hpp>
#include <cpp11/integers.hpp>

#include <tinystring/TinyStrings.h>
#include <tinystring_types.h>
#include "null_pointer.cpp"

[[cpp11::register]]
TinyStrings_ptr rcpp_sub(const TinyStrings_ptr& x_ptr, const long long start, const long long end) {
    assert_not_null_pointer(x_ptr);

    TinyStrings *subbed = x_ptr->subbed(start, end);
    TinyStrings_ptr subbed_ptr(subbed);

    return subbed_ptr;
}
