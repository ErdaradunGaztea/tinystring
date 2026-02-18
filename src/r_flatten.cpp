#include <cpp11/external_pointer.hpp>
#include <cpp11/strings.hpp>

#include <tinystring/TinyStrings.h>
#include <tinystring_types.h>
#include "null_pointer.cpp"

[[cpp11::register]]
TinyStrings_ptr rcpp_flatten(const TinyStrings_ptr& x_ptr, const cpp11::strings &collapse) {
    assert_not_null_pointer(x_ptr);

    const std::vector<std::string> std_collapse(collapse.cbegin(), collapse.cend());

    TinyStrings *flattened = x_ptr->flattened(std_collapse);
    TinyStrings_ptr flattened_ptr(flattened);

    return flattened_ptr;
}
