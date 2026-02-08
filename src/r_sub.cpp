#include <cpp11/external_pointer.hpp>
#include <cpp11/integers.hpp>

#include "TinyStrings.h"
#include "null_pointer.cpp"

[[cpp11::register]]
SEXP rcpp_sub(SEXP x, const std::size_t start, const std::size_t end) {
    const cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    // TODO: do not remove 1 for negative indices (when started to support them)
    TinyStrings *subbed = x_ptr->subbed(start - 1, end - 1);
    cpp11::external_pointer<TinyStrings> subbed_ptr(subbed);

    return subbed_ptr;
}
