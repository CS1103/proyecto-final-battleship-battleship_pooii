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

/**
 * Does the handshake in stage of the program.
 */
void handshake_write(std::string name)
{
    std::string outfile_name = "Player.in";
    std::ofstream outfile(outfile_name);
    if (!outfile)
    {
        throw std::runtime_error("Couldn't open '" + outfile_name +
                                 " for writing.");
    }
    outfile << "HANDSHAKE=" << name << std::endl;
    outfile.close();
}

/**
 * Looks for a filename that matches the regex and returns an std::ofstream if
 * one is found, else the option is empty.
 */
std::optional<std::ifstream> open_file(std::regex r)
{
    // auto path = std::filesystem::current_path() / "test";
    return std::optional<std::ifstream>();
}
