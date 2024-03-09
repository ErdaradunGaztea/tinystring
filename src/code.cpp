#include <cpp11/external_pointer.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/strings.hpp>

#include <string>
#include <vector>

#include "alphabet.cpp"
#include "null_pointer.cpp"

[[cpp11::register]]
SEXP rcpp_alphabet(cpp11::strings letters) {
  std::vector<std::string> letters_std(letters.begin(), letters.end());
  auto alphabet = new Alphabet(letters_std);
  cpp11::external_pointer<Alphabet> alphabet_ptr(alphabet);
  return alphabet_ptr;
}

[[cpp11::register]]
cpp11::integers rcpp_get_alph_size(SEXP x) {
  cpp11::external_pointer<Alphabet> alphabet_ptr(x);
  assert_not_null_pointer(alphabet_ptr);
  return cpp11::as_sexp(alphabet_ptr->get_size());
}

void rcpp_delete_alphabet(SEXP x) {
  cpp11::external_pointer<Alphabet> alphabet_ptr(x);
  delete &(*alphabet_ptr);
}

// When trying to optimize deconstructing long input strings:
// https://cpp11.r-lib.org/articles/FAQ.html#ok-but-i-really-want-to-call-cpp11unwind_protect-manually
