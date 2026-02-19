#include <cpp11/external_pointer.hpp>
#include <cpp11/list_of.hpp>
#include <cpp11/strings.hpp>

#include <tinystring/TinyStrings.h>
#include <tinystring_types.h>
#include "null_pointer.cpp"

[[cpp11::register]]
TinyStrings_ptr rcpp_c(const cpp11::list_of<TinyStrings_ptr> &dots, const cpp11::strings &sep) {
    for (const TinyStrings_ptr &x_ptr : dots) {
        assert_not_null_pointer(x_ptr);
    }

    const auto combined = new TinyStrings(*static_cast<TinyStrings_ptr>(dots.at(0)).get());
    TinyStrings_ptr combined_ptr(combined);

    for (auto it = std::next(dots.cbegin()); it != dots.cend(); ++it) {
        combined->append(*static_cast<TinyStrings_ptr>(*it));
    }

    return combined_ptr;
}
