cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(find-cxx)

add_executable(find-cxx src/main.cpp src/find-cxx.cpp)
target_include_directories(find-cxx PRIVATE include)
