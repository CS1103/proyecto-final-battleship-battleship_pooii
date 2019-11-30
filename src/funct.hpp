#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <utility>

std::map<std::string,std::string> read(std::ifstream& file);

void handshake_write(std::string name);

//std::pair<size_t,std::pair<size_t, size_t>>

std::optional<std::ifstream> open_file(std::regex r);

//std::ofstream placement(int accepted, std::string TOKEN);
