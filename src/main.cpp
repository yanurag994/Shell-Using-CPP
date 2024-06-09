#include <iostream>
#include <vector>
#include <algorithm>

const bool is_supported(const std::string& command)
{
  const std::vector<std::string> supported_commands = { "cd","echo" };
  return std::binary_search(supported_commands.begin(), supported_commands.end(), command);
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
    if (is_supported(input))
    {
      //To be implemented
    }
    else
      std::cout << input << ": command not found\n";
  }
}
