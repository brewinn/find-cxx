# find-cxx
A small `find`-like cli utility

## Description
A small personal project.

To build, you'll want to install [Google Test](https://google.github.io/googletest/) or remove the lines regarding testing from the `CMakeLists.txt`. 
The steps to build are the usual `cmake -S . -B build; cmake --build build`, and the program can then be run with, for example, `build/find-cxx -p test/find-test -n x.*y`.
The tests, if built, can be run with `build/find-cxx-test`.
