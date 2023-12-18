#include <cpp11/r_string.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/external_pointer.hpp>

#include <string>
#include <vector>

[[cpp11::register]]
cpp11::external_pointer<std::string> rcpp_pack(cpp11::strings x) {
  std::vector<std::string> value = {};
  for (auto s : x) {
    value.push_back(s);
  }
  auto ptr = cpp11::external_pointer<std::string>(&value[0]);
  return ptr;
}

[[cpp11::register]]
cpp11::r_string rcpp_unpack(cpp11::external_pointer<std::string> x) {
  std::string x_dptr = *x;
  return x_dptr;
}
