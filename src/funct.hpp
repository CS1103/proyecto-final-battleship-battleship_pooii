#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <utility>
char randchar();

template<typename entero_t>
entero_t randint(entero_t first, entero_t last);

void update(std::pair<std::pair<size_t,size_t>, bool>& point);
std::map<std::string,std::string> read(std::ifstream& file);
std::pair<std::pair<size_t,size_t>, bool> rand_point(std::set<std::pair<std::pair<size_t,size_t>, bool>> data);
bool verify(std::set<std::pair<std::pair<size_t,size_t>, bool>> data, std::pair<std::pair<size_t,size_t>, bool> point);
std::pair<std::pair<size_t,size_t>, bool> generate_point();
void handshake_write(std::string name);

//std::pair<size_t,std::pair<size_t, size_t>>

std::optional<std::ifstream> open_file(std::regex r);

void placement(std::string TOKEN);

void place_boat(char, std::set<std::pair<std::pair<size_t,size_t>, bool>>& tablero);
std::pair<std::pair<size_t,size_t>,char> can_it_place(int len, std::set<std::pair<std::pair<size_t,size_t>, bool>>& tablero);