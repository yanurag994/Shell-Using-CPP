#include <string>

void handleEcho(const std::string&); //Prints the passed arguments back on console
void handleType(const std::string&); //Prints the passed command's type back on console
void handlePwd();
void handleCd(const std::string&);
void handleExecutable(const std::string&, const std::string&); //Inputs command and corresponding arguments and executes