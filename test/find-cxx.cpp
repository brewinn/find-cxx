#include "find-cxx.hpp"
#include "argument-parsing.hpp"
#include <gtest/gtest.h>

TEST(FindCxx, FindByName) {
  auto results = find_by_name("test/find-test/", "xyz");
  EXPECT_EQ(1, results.size());
  EXPECT_STREQ("test/find-test/a/xyz", results[0].path().c_str());
}

TEST(FindCxx, FindByNameWithRegex) {
  auto results = find_by_name("test/find-test/", "x.*z");
  EXPECT_EQ(2, results.size());
  EXPECT_STREQ("test/find-test/a/c/xyyz", results[0].path().c_str());
  EXPECT_STREQ("test/find-test/a/xyz", results[1].path().c_str());
}

TEST(FindCxx, FindByType) {
  auto results = find_by_type("test/find-test/", 'l');
  EXPECT_EQ(1, results.size());
  EXPECT_STREQ("test/find-test/a/b/b.l", results[0].path().c_str());
}

TEST(FindCxx, BadType) {
  int bad_type_exit_code = 3;
  EXPECT_EXIT(find_by_type("test/find-test/", 'q'),
              testing::ExitedWithCode(bad_type_exit_code), "Invalid type");
}

TEST(FindCxx, BadRegex) {
  int bad_regex_exit_code = 4;
  EXPECT_EXIT(find_by_name("test/find-test/", "["),
              testing::ExitedWithCode(bad_regex_exit_code),
              "regular expression");
}
