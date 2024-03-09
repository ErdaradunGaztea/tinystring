// Generated by cpp11: do not edit by hand
// clang-format off


#include "cpp11/declarations.hpp"
#include <R_ext/Visibility.h>

// code.cpp
SEXP rcpp_alphabet(cpp11::strings letters);
extern "C" SEXP _tinystring_rcpp_alphabet(SEXP letters) {
  BEGIN_CPP11
    return cpp11::as_sexp(rcpp_alphabet(cpp11::as_cpp<cpp11::decay_t<cpp11::strings>>(letters)));
  END_CPP11
}
// code.cpp
cpp11::integers rcpp_get_alph_size(SEXP x);
extern "C" SEXP _tinystring_rcpp_get_alph_size(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(rcpp_get_alph_size(cpp11::as_cpp<cpp11::decay_t<SEXP>>(x)));
  END_CPP11
}
// pack.cpp
SEXP rcpp_vpack(cpp11::strings x);
extern "C" SEXP _tinystring_rcpp_vpack(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(rcpp_vpack(cpp11::as_cpp<cpp11::decay_t<cpp11::strings>>(x)));
  END_CPP11
}
// pack.cpp
cpp11::strings rcpp_vunpack(SEXP x);
extern "C" SEXP _tinystring_rcpp_vunpack(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(rcpp_vunpack(cpp11::as_cpp<cpp11::decay_t<SEXP>>(x)));
  END_CPP11
}
// pack.cpp
SEXP rcpp_append_a(SEXP x);
extern "C" SEXP _tinystring_rcpp_append_a(SEXP x) {
  BEGIN_CPP11
    return cpp11::as_sexp(rcpp_append_a(cpp11::as_cpp<cpp11::decay_t<SEXP>>(x)));
  END_CPP11
}

extern "C" {
static const R_CallMethodDef CallEntries[] = {
    {"_tinystring_rcpp_alphabet",      (DL_FUNC) &_tinystring_rcpp_alphabet,      1},
    {"_tinystring_rcpp_append_a",      (DL_FUNC) &_tinystring_rcpp_append_a,      1},
    {"_tinystring_rcpp_get_alph_size", (DL_FUNC) &_tinystring_rcpp_get_alph_size, 1},
    {"_tinystring_rcpp_vpack",         (DL_FUNC) &_tinystring_rcpp_vpack,         1},
    {"_tinystring_rcpp_vunpack",       (DL_FUNC) &_tinystring_rcpp_vunpack,       1},
    {NULL, NULL, 0}
};
}

extern "C" attribute_visible void R_init_tinystring(DllInfo* dll){
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
  R_forceSymbols(dll, TRUE);
}
