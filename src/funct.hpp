#include <fstream>
#include <map>
#include <string>
#include <utility>

std::map<std::string,std::string> read(std::ifstream& file);

void handshake();
//std::pair<size_t,std::pair<size_t, size_t>>
void parse(std::map<std::string,std::string> data);
void placeFleet();
bool verify();