// Generated by cpp11: do not edit by hand
// clang-format off


#include "cpp11/declarations.hpp"
#include <R_ext/Visibility.h>

// code.cpp
cpp11::external_pointer<int> foo();
extern "C" SEXP _tinystring_foo() {
  BEGIN_CPP11
    return cpp11::as_sexp(foo());
  END_CPP11
}
// code.cpp
int baz(SEXP a);
extern "C" SEXP _tinystring_baz(SEXP a) {
  BEGIN_CPP11
    return cpp11::as_sexp(baz(cpp11::as_cpp<cpp11::decay_t<SEXP>>(a)));
  END_CPP11
}
// code.cpp
int bar(cpp11::external_pointer<int> a_pointer);
extern "C" SEXP _tinystring_bar(SEXP a_pointer) {
  BEGIN_CPP11
    return cpp11::as_sexp(bar(cpp11::as_cpp<cpp11::decay_t<cpp11::external_pointer<int>>>(a_pointer)));
  END_CPP11
}

extern "C" {
static const R_CallMethodDef CallEntries[] = {
    {"_tinystring_bar", (DL_FUNC) &_tinystring_bar, 1},
    {"_tinystring_baz", (DL_FUNC) &_tinystring_baz, 1},
    {"_tinystring_foo", (DL_FUNC) &_tinystring_foo, 0},
    {NULL, NULL, 0}
};
}

extern "C" attribute_visible void R_init_tinystring(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
