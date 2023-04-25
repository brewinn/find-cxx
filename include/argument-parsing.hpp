#ifndef ARGUMENT_PARSING_HEADER
#define ARGUMENT_PARSING_HEADER
#include <optional>
#include <string>

struct arguments {
  bool help;
  bool version;
  std::optional<const std::string> path;
  std::optional<const std::string> name;
  std::optional<const char> type;
};

arguments parse_arguments(int argc, char **argv);

#endif
