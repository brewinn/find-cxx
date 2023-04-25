#ifndef HEADER_FIND_CXX__
#define HEADER_FIND_CXX__

#include <filesystem>
#include <string>
#include <vector>

std::vector<std::filesystem::directory_entry>
find_by_name(const std::string_view path, const std::string name);
std::vector<std::filesystem::directory_entry>
find_by_type(const std::string_view path, const char type);

#endif
