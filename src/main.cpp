#include <algorithm>
#include <iostream>

#include "argument-parsing.hpp"
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

void print_paths(std::vector<std::filesystem::directory_entry> entries) {
  for (auto &entry : entries) {
    std::cout << entry.path().c_str() << "\n";
  }
}

int main(const int argc, const char *argv[]) {
  if (argc < 2) {
    help();
    return 2;
  }

  arguments args = parse_arguments(argc, argv);

  if (args.help) {
    help();
    return 0;
  }

  if (args.version) {
    version();
    return 0;
  }

  using namespace std::string_literals;

  if (args.name) {
    auto entries = find_by_name(args.path.value_or("."s), args.name.value());
    print_paths(entries);
    return 0;
  }

  if (args.type) {
    auto entries = find_by_type(args.path.value_or("."s), args.type.value());
    print_paths(entries);
    return 0;
  }

  return 1;
}
