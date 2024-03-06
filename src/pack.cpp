#include <cpp11/strings.hpp>
#include <cpp11/external_pointer.hpp>

#include <string>
#include <vector>

[[cpp11::register]]
SEXP rcpp_vpack(cpp11::strings x) {
  cpp11::external_pointer<std::vector<std::string>> x_ptr(new std::vector<std::string>(x.begin(), x.end()));
  return x_ptr;
}

[[cpp11::register]]
cpp11::strings rcpp_vunpack(SEXP x) {
  cpp11::external_pointer<std::vector<std::string>> x_ptr(x);
  return cpp11::as_sexp(*x_ptr);
}

[[cpp11::register]]
SEXP rcpp_append_a(SEXP x) {
  cpp11::external_pointer<std::vector<std::string>> x_ptr(x);
  x_ptr->push_back("a");
  return x_ptr;
}
