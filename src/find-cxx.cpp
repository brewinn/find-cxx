#include "find-cxx.hpp"
#include <iostream>

void find_by_name(const char *path, const char *name) {
  std::cout << "Find by name " << name << "on path " << path << "\n";
}

void find_by_type(const char *path, const char type) {
  std::cout << "Find by type " << type << " on path " << path << "\n";
}
