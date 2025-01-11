#include <cpp11/strings.hpp>
#include <cpp11/list_of.hpp>
#include <cpp11/external_pointer.hpp>

#include "TinyStrings.h"
#include "null_pointer.cpp"

[[cpp11::register]]
SEXP rcpp_recode(SEXP x, const cpp11::list_of<cpp11::strings> &recodes) {
    cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    const cpp11::strings next = recodes.names();
    std::vector<char> std_next;
    std::transform(next.cbegin(), next.cend(), std::back_inserter(std_next), [](const cpp11::r_string &s) {
        return std::string(s).at(0);
    });

    std::vector<char> std_prev;
    std::transform(recodes.cbegin(), recodes.cend(), std::back_inserter(std_prev), [](const cpp11::strings &s) {
        return std::string(s.at(0)).at(0);
    });

    const auto recoded = new TinyStrings(*x_ptr);
    // ReSharper disable once CppTemplateArgumentsCanBeDeduced
    cpp11::external_pointer<TinyStrings> recoded_ptr(recoded);

    for (uint32_t i = 0; i < std_prev.size(); i++) {
        recoded_ptr->get_alphabet().recode_letter(std_prev.at(i), std_next.at(i));
    }

    return recoded_ptr;
}

[[cpp11::register]]
SEXP rcpp_ip_recode(SEXP x, const cpp11::list_of<cpp11::strings> &recodes) {
    cpp11::external_pointer<TinyStrings> x_ptr(x);
    assert_not_null_pointer(x_ptr);

    const cpp11::strings next = recodes.names();
    std::vector<char> std_next;
    std::transform(next.cbegin(), next.cend(), std::back_inserter(std_next), [](const cpp11::r_string &s) {
        return std::string(s).at(0);
    });

    std::vector<char> std_prev;
    std::transform(recodes.cbegin(), recodes.cend(), std::back_inserter(std_prev), [](const cpp11::strings &s) {
        return std::string(s.at(0)).at(0);
    });

    for (uint32_t i = 0; i < std_prev.size(); i++) {
        x_ptr->get_alphabet().recode_letter(std_prev.at(i), std_next.at(i));
    }

    return x_ptr;
}
