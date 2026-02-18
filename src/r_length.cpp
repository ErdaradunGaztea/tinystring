#include <cpp11/external_pointer.hpp>
#include <cpp11/integers.hpp>

#include <tinystring/TinyStrings.h>
#include <tinystring_types.h>
#include "null_pointer.cpp"

[[cpp11::register]]
cpp11::writable::integers rcpp_length(const TinyStrings_ptr& x_ptr) {
    assert_not_null_pointer(x_ptr);

    const auto sizes = x_ptr->sizes();

    return {sizes.cbegin(), sizes.cend()};
}

[[cpp11::register]]
std::size_t rcpp_num_strings(const TinyStrings_ptr& x_ptr) {
    assert_not_null_pointer(x_ptr);

    return x_ptr->get_data().size();
}

[[cpp11::register]]
TinyStrings_ptr rcpp_set_length(const TinyStrings_ptr& x_ptr, const int size) {
    assert_not_null_pointer(x_ptr);

    x_ptr->get_data().resize(size, TinyString(x_ptr->get_alphabet()));

    return x_ptr;
}
