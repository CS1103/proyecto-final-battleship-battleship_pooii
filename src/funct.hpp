#include <fstream>
#include <map>
#include <regex>
#include <string>
#include <utility>

std::map<std::string,std::string> read(std::ifstream& file);



//std::pair<size_t,std::pair<size_t, size_t>>

std::optional<std::ifstream> open_file(std::regex r);


std::vector<std::pair<std::pair<size_t, size_t>,
                      std::pair<size_t, size_t>>>
    adjacent_positions(std::pair<size_t, size_t> pos, size_t rows, size_t cols);

