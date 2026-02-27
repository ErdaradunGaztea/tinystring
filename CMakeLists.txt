cmake_minimum_required(VERSION 3.30)
project(tinystring)

set(CMAKE_CXX_STANDARD 17)

include_directories(inst/include)
include_directories(C:/Program\ Files/R/R-4.4.1/include)
include_directories(C:/Users/erdar/AppData/Local/R/win-library/4.4/cpp11/include)

add_library(tinystring STATIC
        inst/include/tinystring/Alphabet.h
        inst/include/tinystring/AlphabetSimple.h
        inst/include/tinystring/TinyStrings.h
        inst/include/tinystring/TinyString.h
        inst/include/tinystring/const.h
        inst/include/tinystring_types.h
        inst/include/tinystring/regex/State.h
        inst/include/tinystring/regex/Rule.h
        inst/include/tinystring/regex/epsilon.h
        inst/include/tinystring/regex/Graph.h
        inst/include/tinystring/regex/matchers.h
)
set_target_properties(tinystring PROPERTIES LINKER_LANGUAGE CXX)

add_executable(tinystring-test
        src/null_pointer.cpp
        src/r_unpack.cpp
        src/r_pack.cpp
        src/r_length.cpp
        src/r_recode.cpp
        src/r_flatten.cpp
        src/r_sub.cpp
        src/r_alphabet.cpp
        src/r_c.cpp)
target_link_libraries(tinystring-test tinystring)