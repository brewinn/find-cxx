#include <algorithm>
#include <iostream>

#include "argument-parsing.hpp"

// Borrowing from
// https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
// {
char *getCmdOption(char **begin, char **end, const std::string &option) {
  char **itr = std::find(begin, end, option);
  if (itr != end && ++itr != end) {
    return *itr;
  }
  return 0;
}

bool cmdOptionExists(char **begin, char **end, const std::string &option) {
  return std::find(begin, end, option) != end;
}
// }

// Helper function, return the option if either the long or short version was
// specified
const char *parse_option(char **args_start, char **args_end,
                         const char *short_option, const char *long_option) {
  char *option = getCmdOption(args_start, args_end, short_option);
  if (option != nullptr) {
    return option;
  }

  option = getCmdOption(args_start, args_end, long_option);
  if (option != nullptr) {
    return option;
  }

  return nullptr;
}

arguments parse_arguments(int argc, char **argv) {
  char **args_start = argv;
  char **args_end = argv + argc;

  arguments args;
  bool help, version;
  std::optional<std::string> path, name;
  std::optional<char> type;

  if (cmdOptionExists(args_start, args_end, "-h") ||
      cmdOptionExists(args_start, args_end, "--help")) {
    help = true;
  } else {
    help = false;
  }

  if (cmdOptionExists(args_start, args_end, "-v") ||
      cmdOptionExists(args_start, args_end, "--version")) {
    version = true;
  } else {
    version = false;
  }

  // For convenience, we can capture the args in a lambda, so we need only
  // specify the long and short option
  auto parse_arg = [=](const char *short_option, const char *long_option) {
    return parse_option(args_start, args_end, short_option, long_option);
  };

  const char *parsed_path = parse_arg("-p", "--path");
  if (parsed_path == nullptr) {
    path = std::nullopt;
  } else {
    path = std::basic_string(parsed_path);
  }

  const char *parsed_name = parse_arg("-n", "--name");
  if (parsed_name == nullptr) {
    name = std::nullopt;
  } else {
    name = std::basic_string(parsed_name);
  }

  const char *parsed_type = parse_arg("-t", "--type");
  if (parsed_type == nullptr) {
    type = std::nullopt;
  } else {
    type = *parsed_type;
  }
  return {
      .help = help,
      .version = version,
      .path = path,
      .name = name,
      .type = type,
  };
}
