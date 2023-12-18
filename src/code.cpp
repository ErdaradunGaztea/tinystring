#include <cpp11/external_pointer.hpp>
#include <vector>
#include <string>

[[cpp11::register]]
cpp11::external_pointer<int> foo() {
  auto ptr = cpp11::external_pointer<int>(new int(1));

  return ptr;
}

[[cpp11::register]]
int baz(SEXP a) {
  cpp11::external_pointer<int> a_pointer(a);

  int b = *a_pointer;

  return b;
}

[[cpp11::register]]
int bar(cpp11::external_pointer<int> a_pointer) {
  int b = *a_pointer;

  return b;
}

// When trying to optimize deconstructing long input strings:
// https://cpp11.r-lib.org/articles/FAQ.html#ok-but-i-really-want-to-call-cpp11unwind_protect-manually
