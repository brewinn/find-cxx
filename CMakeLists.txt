cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(find-cxx)

add_executable(find-cxx src/main.cpp src/find-cxx.cpp src/argument-parsing.cpp)
target_include_directories(find-cxx PRIVATE include)

# For testing
enable_testing()
find_package(GTest REQUIRED)

add_executable(
  find-cxx-test
  src/argument-parsing.cpp
  src/find-cxx.cpp
  test/find-cxx.cpp
  test/argument-parsing.cpp)

target_include_directories(find-cxx-test PRIVATE include)
target_link_libraries(
  find-cxx-test
  GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(find-cxx-test)
