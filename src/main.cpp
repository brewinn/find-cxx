#include <algorithm>
#include <iostream>

#include "find-cxx.hpp"

void help() {
  std::cout << "USAGE:\n"
               "find-cxx [OPTIONS] [PATH] \n"
               "\n"
               "FLAGS:\n"
               "-h, --help              Display help information\n"
               "-v, --version           Display information information\n"
               "\n"
               "OPTIONS:\n"
               "-n, --name <NAME>    Name\n"
               "-t, --type <TYPE>    Entry type [possible values: f, d, l]\n"
               "-p, --path <PATH>    Search path [default: .]\n"
               "";
}

void version() { std::cout << "find-cxx 0.1.0\n"; }

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

int main(int argc, char *argv[]) {
  if (argc < 2) {
    help();
    return 2;
  }

  char **args_start = argv;
  char **args_end = argv + argc;
  if (cmdOptionExists(args_start, args_end, "-h") ||
      cmdOptionExists(args_start, args_end, "--help")) {
    help();
    return 0;
  }

  if (cmdOptionExists(args_start, args_end, "-v") ||
      cmdOptionExists(args_start, args_end, "--version")) {
    version();
    return 0;
  }

  // For convenience, we can capture the args in a lambda, so we need only
  // specify the long and short option
  auto parse_arg = [=](const char *short_option, const char *long_option) {
    return parse_option(args_start, args_end, short_option, long_option);
  };

  const char *path = parse_arg("-p", "--path");
  if (path == nullptr) {
    path = ".";
  }

  const char *name = parse_arg("-n", "--name");
  if (name) {
    find_by_name(path, name);
    return 0;
  }

  const char *type = parse_arg("-t", "--type");
  if (type) {
    find_by_type(path, *type);
    return 0;
  }

  help();
  return 1;
}
