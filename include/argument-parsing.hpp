#ifndef ARGUMENT_PARSING_HEADER
#define ARGUMENT_PARSING_HEADER
#include <optional>
#include <string>

struct arguments {
  bool help = false;
  bool version = false;
  std::optional<const std::string> path = std::nullopt;
  std::optional<const std::string> name = std::nullopt;
  std::optional<const char> type = std::nullopt;

  friend bool operator==(const arguments &lhs, const arguments &rhs);
};

arguments parse_arguments(int argc, const char **argv);

#endif
