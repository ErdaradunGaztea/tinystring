#include <cpp11/external_pointer.hpp>
#include <cpp11/integers.hpp>

#include "TinyStrings.h"
#include "null_pointer.cpp"

[[cpp11::register]]
cpp11::writable::integers rcpp_length(SEXP x) {
  cpp11::external_pointer<TinyStrings> x_ptr(x);
  assert_not_null_pointer(x_ptr);

  auto sizes = x_ptr->sizes();

  return cpp11::writable::integers(sizes.cbegin(), sizes.cend());
}

[[cpp11::register]]
int rcpp_num_strings(SEXP x) {
  cpp11::external_pointer<TinyStrings> x_ptr(x);
  assert_not_null_pointer(x_ptr);

  return x_ptr->get_data().size();
}

[[cpp11::register]]
SEXP rcpp_set_length(SEXP x, int size) {
  cpp11::external_pointer<TinyStrings> x_ptr(x);
  assert_not_null_pointer(x_ptr);

  x_ptr->get_data().resize(size);

  return x_ptr;
}
