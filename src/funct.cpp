#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

#include "funct.hpp"
#include "prettyprint.hpp"

std::map<std::string,std::string> read(std::ifstream& file)
{
    std::map<std::string,std::string> data;    
    std::string tmp;
    std::getline(file, tmp);
    std::string line;
    
    while (std::getline(file, line,'='))
    {
        std::string line2;

        std::getline(file, line2);
        data[line] = line2;
    }

    return data;
}

void open_outfile(std::ofstream& out)
{
    // XXX: Is there a better way to do this
    static std::string outfile_name = "Player.in";
    std::ofstream outfile(outfile_name);
    if (!outfile)
    {
        throw std::runtime_error("Couldn't open '" + outfile_name +
                                 " for writing.");
    }

    out = std::move(outfile);
}

/**
 * Does the handshake in stage of the program.
 */
void handshake_write(std::string name)
{
    std::ofstream outfile;
    open_outfile(outfile);

    outfile << "HANDSHAKE=" << name << std::endl;
    outfile.close();
}

#include <string>
std::string coordinate_to_letters(size_t c) {
    std::string ret(1, 'A' + c % 26);
    c /= 26;

    while (c != 0)
    {
        ret = std::string(1, 'A' - 1 + c % 27) + ret;
        c /= 27;
    }

    return ret;
}

void attack_position(size_t x, size_t y, size_t token)
{
    std::ofstream outfile;
    open_outfile(outfile);

    outfile << "TOKEN=" << token << std::endl;
    outfile << "ATTACK=" << coordinate_to_letters(y) << x << std::endl;
}

/**
 * Looks for a filename that matches the regex and returns an std::ifstream if
 * one is found, else the option is empty.
 */
std::optional<std::ifstream> open_file(std::regex r)
{
    std::string path = std::filesystem::current_path();

    for (auto const& entry : std::filesystem::directory_iterator(path))
    {
        std::string a = entry.path();
        // XXX: Can't you pass entry.path() directly?
        if(regex_match(a.begin(), a.end(), r))
        {
           return std::ifstream(entry.path());
        }
    }

    return std::optional<std::ifstream>();
}

std::vector<std::pair<std::pair<size_t, size_t>,
                      std::pair<size_t, size_t>>>
adjacent_positions(std::pair<size_t, size_t> pos,
                   std::pair<size_t, size_t> map_size)
{
    static std::vector<std::pair<int, int>> possible_moves = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    size_t x = pos.first;
    size_t y = pos.second;

    std::vector<std::pair<std::pair<size_t, size_t>,
                          std::pair<size_t, size_t>>>
        ret;

    for (auto const& pm : possible_moves)
    {
        if (is_inside_map({x + pm.first, y + pm.second}, map_size))
        {
            ret.emplace_back(std::make_pair(x + pm.first, y + pm.second), pm);
        }
    }

    return ret;
}

/**
 * Checks wheter a given position is inside a maps boundaries
 */
bool is_inside_map(std::pair<size_t, size_t> pos, std::pair<size_t,
                   size_t> map_size)
{
    return pos.first < map_size.first && pos.second < map_size.second;
}
