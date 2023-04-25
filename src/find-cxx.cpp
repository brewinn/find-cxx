#include "find-cxx.hpp"
#include <iostream>
#include <regex>

namespace fs = std::filesystem;

std::vector<std::filesystem::directory_entry>
find_by_name(const std::string_view path, const std::string name) {
  std::vector<fs::directory_entry> results;
  try {
    std::regex re(name);
    for (const auto &entry : fs::recursive_directory_iterator(path)) {
      if (std::regex_search(entry.path().c_str(), re)) {
        results.push_back(entry);
      }
    }
  } catch (const std::regex_error &e) {
    std::cerr << "Error in forming regular expression: " << e.what() << '\n';
    std::exit(4);
  }
  return results;
}

std::vector<std::filesystem::directory_entry>
find_by_type(const std::string_view path, const char type) {
  std::vector<fs::directory_entry> results;
  // Check for valid type
  // Maybe an enum or variant would also work, but I like the simplicity of just
  // using char
  switch (type) {
  case 'l': {
    for (auto entry : fs::recursive_directory_iterator(path)) {
      if (fs::is_symlink(entry)) {
        results.push_back(entry);
      }
    }
    break;
  }
  case 'f':
    for (auto entry : fs::recursive_directory_iterator(path)) {
      if (fs::is_regular_file(entry)) {
        results.push_back(entry);
      }
    }
    break;
  case 'd':
    for (auto entry : fs::recursive_directory_iterator(path)) {
      if (fs::is_directory(entry)) {
        results.push_back(entry);
      }
    }
    break;
  default:
    std::cerr << "Invalid type\n";
    std::exit(3);
  }
  return results;
}
