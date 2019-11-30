#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <utility>

std::map<std::string,std::string> read(std::ifstream& file);

void handshake_write(std::string name);

std::string coordinate_to_letters(size_t c);

//std::pair<size_t,std::pair<size_t, size_t>>

std::optional<std::ifstream> open_file(std::regex r);

void attack_position(size_t x, size_t y, size_t token);

std::vector<std::pair<std::pair<size_t, size_t>,
                      std::pair<size_t, size_t>>>
    adjacent_positions(std::pair<size_t, size_t> pos, size_t rows, size_t cols);

bool is_inside_map(std::pair<size_t, size_t> pos,
                   std::pair<size_t, size_t> map_size);
