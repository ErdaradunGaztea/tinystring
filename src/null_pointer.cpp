#include <cpp11/external_pointer.hpp>

template<class T>
void assert_not_null_pointer(cpp11::external_pointer<T> ptr) {
    if (ptr.get() == nullptr) {
        cpp11::stop("Null pointer!");
    }
}
