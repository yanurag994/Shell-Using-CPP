#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>

enum cmd {
  exit_cmd, echo, type,
  cd,
  invalid
};

const static std::map<std::string, cmd> enum_map_cmd = {
    {"exit", exit_cmd},
    {"cd", cd},
    {"echo", echo},
    {"type",type},
    { "",invalid }
};

cmd get_command_enum(const std::string& command) {
  auto it = enum_map_cmd.find(command);
  if (it != enum_map_cmd.end()) {
    return it->second;
  }
  return invalid;
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
      for (size_t idx = 1;idx < command.size() - 1;idx++) {
        std::cout << command[idx] << ' ';
      }
      std::cout << command[command.size() - 1] << '\n';
      break;
    }
    case cd: {
      break;
    }
    case type: {
      if (get_command_enum(command[1]) < 3)
        std::cout << command[1] << " is a shell builtin\n";
      else if (get_command_enum(command[1]) == invalid)
        std::cout << command[1] << " not found\n";
      else
        std::cout << command[1] << '\n';
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
