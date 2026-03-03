#include <cpp11/external_pointer.hpp>
#include <cpp11/logicals.hpp>

#include <tinystring/TinyStrings.h>
#include <tinystring_types.h>
#include <tinystring/regex/Graph.h>
#include <tinystring/regex/matchers.h>

#include "null_pointer.cpp"

[[cpp11::register]]
cpp11::writable::logicals rcpp_match(const TinyStrings_ptr& x_ptr) {
    assert_not_null_pointer(x_ptr);

    const auto alphabet = x_ptr->get_alphabet();
    const auto first_letter_regex = match_letter(alphabet.match_index(alphabet.get_letters().at(0)));
    const auto any_letter_regex = match_any();
    const auto two_letter_regex = concat(first_letter_regex, any_letter_regex);
    const auto regex = zero_or_more(two_letter_regex);

    std::vector<bool> results(x_ptr->size());

    std::transform(x_ptr->get_data().cbegin(), x_ptr->get_data().cend(), results.begin(), [regex](const auto& string) {
        return regex.match(string);
    });

    return {results};
}
