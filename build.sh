#!/bin/sh

run_cmake()
{
 echo Running CMake...
 cd build || (echo Failed to enter build directory ; exit)
 cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
}

build()
{
  echo Building...
  cmake --build .
}

run_cmake
build
