#include <filesystem>

#include "commands.hpp"

std::pair<std::string, std::string> parse_command(const std::string& input) {
  size_t space_pos = input.find_first_of(' ');
  return (space_pos == std::string::npos) ?
    std::make_pair(input, "") :
    std::make_pair(input.substr(0, space_pos), input.substr(space_pos + 1));
}

cmd get_command_enum(const std::string& command) {
    auto it = enum_map_cmd.find(command);
    if (it != enum_map_cmd.end()) {
        return it->second;
    }
    return executable;
}

std::string get_command_path(const std::string& command_str) {
  const char* path_env = getenv("PATH");
  if (!path_env) {
    throw std::runtime_error("PATH environment variable not found");
  }

  std::string paths(path_env);
  size_t p_idx = 0, c_idx;
  std::string path;

  while ((c_idx = paths.find(':', p_idx)) != std::string::npos) {
    std::string path = paths.substr(p_idx, c_idx - p_idx) + '/' + command_str;
    if (std::filesystem::exists(path))
      return path;
    p_idx = c_idx + 1;
  }
  if (p_idx < paths.length()) {
    std::string path = paths.substr(p_idx) + '/' + command_str;
    if (std::filesystem::exists(path))
      return path;
  }
  return "";
}

