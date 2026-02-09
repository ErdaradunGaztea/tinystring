#include <cpp11/external_pointer.hpp>
#include <cpp11/integers.hpp>

#include "TinyStrings.h"
#include "null_pointer.cpp"

[[cpp11::register]]
cpp11::writable::integers rcpp_length(SEXP x) {
    const cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    const auto sizes = x_ptr->sizes();

    return {sizes.cbegin(), sizes.cend()};
}

[[cpp11::register]]
std::size_t rcpp_num_strings(SEXP x) {
    const cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    return x_ptr->get_data().size();
}

[[cpp11::register]]
SEXP rcpp_set_length(SEXP x, const int size) {
    cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    x_ptr->get_data().resize(size, TinyString(x_ptr->get_alphabet()));

    return x_ptr;
}
