#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>
#include <filesystem>
#include <string_view>

enum cmd {
  exit_cmd, echo, type, non_builtIn
};

const static std::map<std::string, cmd> enum_map_cmd = {
    {"exit", exit_cmd},
    {"echo", echo},
    {"type",type},
};

cmd get_command_enum(const std::string& command) {
  auto it = enum_map_cmd.find(command);
  if (it != enum_map_cmd.end()) {
    return it->second;
  }
  return non_builtIn;
}

std::string get_command_path(const std::string& command_str) {
  const char* path_env = getenv("PATH");
  if (!path_env) {
    throw std::runtime_error("PATH environment variable not found");
  }

  std::string paths(path_env);
  size_t p_idx = 0, c_idx;
  std::string_view path;

  while ((c_idx = paths.find(':', p_idx)) != std::string::npos) {
    path = std::string_view(paths.c_str() + p_idx, c_idx - p_idx);
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
      if (entry.path().filename() == command_str) {
        return entry.path().string();
      }
    }
    p_idx = c_idx + 1;
  }

  // Check the last part of PATH if there are no more colons
  if (p_idx < paths.length()) {
    path = std::string_view(paths.c_str() + p_idx);
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
      if (entry.path().filename() == command_str) {
        return entry.path().string();
      }
    }
  }
  return "";
}

std::vector<std::string> parse_command(const std::string& input) {
  std::vector<std::string> command;
  size_t c_idx = 0, p_idx = 0;

  while ((c_idx = input.find_first_of(' ', p_idx)) != std::string::npos) {
    if (c_idx > p_idx) {
      command.push_back(input.substr(p_idx, c_idx - p_idx));
    }
    p_idx = c_idx + 1;
  }
  if (p_idx < input.length()) command.push_back(input.substr(p_idx));

  return command;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // You can use print statements as follows for debugging, they'll be visible when running tests.
  //std::cout << "Logs from your program will appear here!\n";

  // Uncomment this block to pass the first stage
  while (true) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);
    assert(input.size() > 0);
    std::vector<std::string> command = parse_command(input);
    assert(command.size() > 0);
    switch (get_command_enum(command[0])) {
    case exit_cmd: {
      return 0;
      break;
    }
    case echo: {
      for (size_t idx = 1;idx < command.size();idx++)
        std::cout << command[idx] << (idx + 1 < command.size() ? ' ' : '\n');
      break;
    }
    case type: {
      if (get_command_enum(command[1]) != non_builtIn)
        std::cout << command[1] << " is a shell builtin\n";
      else {
        std::string exec_path = get_command_path(command[1]);
        if (exec_path != "")
          std::cout << command[1] << " is " << exec_path << '\n';
        else
          std::cout << command[1] << ": not found\n";
      }
      break;
    }
    case non_builtIn:
    {
      std::cout << command[0] << ": command not found\n";
      break;
    }
    default:
    {
      std::cout << command[0] << ": command not found\n";
      break;
    }
    }
  }
}
