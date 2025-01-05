cmake_minimum_required(VERSION 3.30)
project(tinystring)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:/Program\ Files/R/R-4.4.1/include)
include_directories(C:/Users/erdar/AppData/Local/R/win-library/4.4/cpp11/include)

# There should be a target that does not use all these R-related files
add_library(tinystring STATIC
        src/Alphabet.h
        src/AlphabetSimple.h
        src/TinyStrings.h
        src/null_pointer.cpp
        src/r_unpack.cpp
        src/r_pack.cpp
        src/r_length.cpp
        src/r_recode.cpp
        src/r_flatten.cpp
)