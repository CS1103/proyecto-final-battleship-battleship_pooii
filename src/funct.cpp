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
 * Looks for a filename that matches the regex and returns an std::ifstream if
 * one is found, else the option is empty.
 */
std::optional<std::ifstream> open_file(std::regex r)
{
    std::string path = std::filesystem::current_path();

    for (const auto & entry : std::filesystem::directory_iterator(path))
    {
        std::string a = entry.path();
        if(regex_match(a.begin(), a.end(), r))
        {
           std::ifstream file(entry.path());
           return file;
        }
    }
    return std::optional<std::ifstream>();
}

// Placement
/*
std::ofstream placement(int accepted, std::string TOKEN)
{
    std::map<char, size_t> remaining_fleet = {
        {'A', 4},
        {'B', 3},
        {'S', 2},
        {'T', 1}
    };

    std::string outfile_name = "FirstPlayer.in";
            std::ofstream outfile(outfile_name);
            if (!outfile)
            {
                throw std::runtime_error("Couldn't open '" + outfile_name +
                                        " for writing.");
            }
    
    switch(accepted)
    {
        case 0:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=B-B1-V" << std::endl;
            outfile.close();
            return outfile;

        break;
        case 1:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=B-G3-H" << std::endl;
            outfile.close();
            return outfile;


        break;
        case 2:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=S-D5-H" << std::endl;
            outfile.close();
            return outfile;

        break;
        case 3:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=S-E7-V" << std::endl;
            outfile.close();
            return outfile;

        break;
        case 4:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=S-H8-H" << std::endl;
            outfile.close();
            return outfile;

        break;
        case 5:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=A-C10-H" << std::endl;
            outfile.close();
            return outfile;

        break;
        case 6:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=T-D2-H" << std::endl;
            outfile.close();
            return outfile;

        break;
        case 7:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=T-H1-H" << std::endl;
            outfile.close();
            return outfile;

        break;
        case 8:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=T-H5-H" << std::endl;
            outfile.close();
            return outfile;

        break;
        case 9:
            outfile << "TOKEN=" << TOKEN << std::endl;
            outfile << "PLACEFLEET=T-H5-H" << std::endl;
            outfile.close();
            return outfile;

        break;
        default:
            return outfile;
    }    
}
*/