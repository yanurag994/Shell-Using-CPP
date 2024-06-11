#include <map>
#include <string>

enum cmd {
    exit_cmd, echo, type, pwd, cd, executable
};

const static std::map<std::string, cmd> enum_map_cmd = {
    {"exit", exit_cmd},
    {"echo", echo},
    {"type",type},
    {"pwd",pwd},
    {"cd",cd}
};

std::pair<std::string, std::string> parse_command(const std::string&);
cmd get_command_enum(const std::string&);
std::string get_command_path(const std::string&);

