#include <cpp11/strings.hpp>
#include <cpp11/external_pointer.hpp>

#include <string>
#include <vector>
#include <algorithm>

#include "TinyStrings.cpp"
#include "null_pointer.cpp"

[[cpp11::register]]
cpp11::strings rcpp_unpack(SEXP x) {
  cpp11::external_pointer<TinyStrings> x_ptr(x);
  assert_not_null_pointer(x_ptr);
  auto unpacked = x_ptr->unpack();
  cpp11::writable::strings ret;
  for (auto sequence : unpacked) {
    ret.push_back(sequence);
  }
  return ret;
}
