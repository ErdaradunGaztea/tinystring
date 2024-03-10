#include <cpp11/strings.hpp>
#include <cpp11/list.hpp>
#include <cpp11/external_pointer.hpp>

#include <string>
#include <vector>

#include "TinyStrings.cpp"

[[cpp11::register]]
SEXP rcpp_pack(cpp11::strings x, cpp11::strings alphabet) {
  std::vector<std::string> std_x(x.begin(), x.end());
  std::vector<std::string> std_alphabet(alphabet.begin(), alphabet.end());
  auto packed = new TinyStrings(std_x, std_alphabet);
  cpp11::external_pointer<TinyStrings> packed_ptr(packed);
  return packed_ptr;
}

[[cpp11::register]]
cpp11::list rcpp_display(SEXP x) {
  cpp11::external_pointer<TinyStrings> x_ptr(x);
  auto codes = x_ptr->get_data();
  cpp11::writable::list ret{};
  for (auto code : codes) {
    ret.push_back(cpp11::as_sexp(code));
  }
  return ret;
}
