#include <cpp11/external_pointer.hpp>

#include "TinyStrings.cpp"
#include "null_pointer.cpp"

[[cpp11::register]]
SEXP rcpp_flatten(SEXP x) {
  cpp11::external_pointer<TinyStrings> x_ptr(x);
  assert_not_null_pointer(x_ptr);

  TinyStrings* flattened = x_ptr->flattened();
  cpp11::external_pointer<TinyStrings> flattened_ptr(flattened);

  return flattened_ptr;
}
