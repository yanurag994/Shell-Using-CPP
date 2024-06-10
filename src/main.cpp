#include <iostream>
#include <vector>
#include <cassert>
#include <string>

#include "handleFunctions.hpp"
#include "commands.hpp"

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

    std::pair<std::string, std::string> command_args = parse_command(input);

    switch (get_command_enum(command_args.first)) {
      case exit_cmd: {
        return 0;
        break;
      }
      case echo: {
        handleEcho(command_args.second);
        break;
      }
      case type: {
        handleType(command_args.second);
        break;
      }
      case pwd:
      {
        handlePwd();
        break;
      }
      case executable:
      {
        handleExecutable(command_args.first, command_args.second);
        break;
      }
      default:
      {
        break;
      }
    }
  }
}
