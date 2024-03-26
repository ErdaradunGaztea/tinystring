#include <cpp11/external_pointer.hpp>

#include "TinyStrings.cpp"
#include "null_pointer.cpp"

[[cpp11::register]]
int rcpp_length(SEXP x) {
  cpp11::external_pointer<TinyStrings> x_ptr(x);
  assert_not_null_pointer(x_ptr);

  return x_ptr->get_data().size();
}

[[cpp11::register]]
SEXP rcpp_set_length(SEXP x, int size) {
  cpp11::external_pointer<TinyStrings> x_ptr(x);
  assert_not_null_pointer(x_ptr);

  printf("Size before: %llu\n", x_ptr->get_data().size());
  x_ptr->get_data().resize(size);
  printf("Size after: %llu\n", x_ptr->get_data().size());

  return x_ptr;
}
