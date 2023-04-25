#include "find-cxx.hpp"
#include <filesystem>
#include <iostream>
#include <regex>

namespace fs = std::filesystem;

void find_by_name(const std::string_view path, const std::string name) {
  try {
    std::regex re(name);
    for (const auto &entry : fs::recursive_directory_iterator(path)) {
      if (std::regex_search(entry.path().c_str(), re)) {
        std::cout << entry.path().c_str() << "\n";
      }
    }
  } catch (const std::regex_error &e) {
    std::cerr << "Error in forming regular expression: " << e.what() << '\n';
    std::exit(4);
  }
}

void find_by_type(const std::string_view path, const char type) {
  // Check for valid type
  // Maybe an enum or variant would also work, but I like the simplicity of just
  // using char
  switch (type) {
  case 'l': {
    for (auto entry : fs::recursive_directory_iterator(path)) {
      if (fs::is_symlink(entry)) {
        std::cout << entry.path().c_str() << '\n';
      }
    }
    break;
  }
  case 'f':
    for (auto entry : fs::recursive_directory_iterator(path)) {
      if (fs::is_regular_file(entry)) {
        std::cout << entry.path().c_str() << '\n';
      }
    }
    break;
  case 'd':
    for (auto entry : fs::recursive_directory_iterator(path)) {
      if (fs::is_directory(entry)) {
        std::cout << entry.path().c_str() << '\n';
      }
    }
    break;
  default:
    std::cerr << "Invalid type\n";
    std::exit(3);
  }
}
