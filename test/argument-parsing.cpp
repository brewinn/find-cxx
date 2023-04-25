#include "argument-parsing.hpp"
#include <gtest/gtest.h>

TEST(ArgumentParsing, HelpFlag) {
  int argc = 2;
  const char *argv[] = {"find-cxx", "-h"};
  arguments args = parse_arguments(argc, argv);
  EXPECT_TRUE(args.help);
}

TEST(ArgumentParsing, VersionFlag) {
  int argc = 2;
  const char *argv[] = {"find-cxx", "-v"};
  arguments args = parse_arguments(argc, argv);
  EXPECT_TRUE(args.version);
}

TEST(ArgumentParsing, MultipleFlags) {
  int argc = 4;
  const char *argv[] = {"find-cxx", "-v", "-h", "xyz"};
  arguments args = parse_arguments(argc, argv);
  arguments expected = {
      .help = true,
      .version = true,
  };
  EXPECT_EQ(args, expected);
}

TEST(ArgumentParsing, Path) {
  int argc = 3;
  const char *argv[] = {"find-cxx", "--path", "xyz"};
  arguments args = parse_arguments(argc, argv);
  arguments expected = {.path = "xyz"};
  EXPECT_EQ(args, expected);
}

TEST(ArgumentParsing, Name) {
  int argc = 3;
  const char *argv[] = {"find-cxx", "--name", "abc"};
  arguments args = parse_arguments(argc, argv);
  arguments expected = {.name = "abc"};
  EXPECT_EQ(args, expected);
}

TEST(ArgumentParsing, Type) {
  int argc = 3;
  const char *argv[] = {"find-cxx", "--type", "f"};
  arguments args = parse_arguments(argc, argv);
  arguments expected = {.type = 'f'};
  EXPECT_EQ(args, expected);
}
