#include <fstream>
#include <map>
#include <string>
#include <utility>

std::map<std::string,std::string> read(std::ifstream& file);

std::pair<size_t,std::pair<size_t, size_t>> handshake();
