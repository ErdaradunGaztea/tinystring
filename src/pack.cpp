#include <cpp11/strings.hpp>
#include <cpp11/external_pointer.hpp>

#include <string>
#include <vector>

[[cpp11::register]]
SEXP rcpp_vpack(cpp11::strings x) {
  auto value = new std::vector<std::string>(x.begin(), x.end());
  cpp11::external_pointer<std::vector<std::string>> x_ptr(value);
  return x_ptr;
}

[[cpp11::register]]
cpp11::strings rcpp_vunpack(SEXP x) {
  cpp11::external_pointer<std::vector<std::string>> x_ptr(x);
  return cpp11::as_sexp(*x_ptr);
}

[[cpp11::register]]
SEXP rcpp_append_a(SEXP x) {
  // The code below changes x in-place! Even if we didn't return x_ptr, the value X is pointing to changes.
  cpp11::external_pointer<std::vector<std::string>> x_ptr(x);
  x_ptr->push_back("a");
  return x_ptr;
}
