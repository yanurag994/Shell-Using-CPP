#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

const bool is_supported(const std::string& command)
{
  const std::vector<std::string> supported_commands = { "cd","echo","exit" };
  return std::binary_search(supported_commands.begin(), supported_commands.end(), command);
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
    if (is_supported(command[0]))
    {
      if (command[0] == "exit") return 0;

      //To be implemented
    }
    else
      std::cout << command[0] << ": command not found\n";
  }
}
