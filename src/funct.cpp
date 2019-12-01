#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <stdexcept>
#include <set>
#include <stdio.h> 
#include <stdlib.h> 
#include <string>
#include <random>
#include <time.h>
#include <utility>
#include <vector>


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
        if (regex_match(a.begin(), a.end(), r))
        {
           std::ifstream file(entry.path());
           return file;
        }
    }
    return std::optional<std::ifstream>();
}

// Placement
// Picks a point and tries either vertical or horizontal placment (rndm)
// If that doesn't work, try the next point in diagonal
void place_boat(char type_ship, std::set<std::pair<std::pair<size_t,size_t>, bool>>& tablero)
{   
    std::vector<std::pair<std::pair<size_t,size_t>,char>> points;
    int len;
    std::pair<std::pair<size_t, size_t>,char> par;
    switch (type_ship)
    {   
        case 'A':
            len = 4;
            par = can_it_place(len, tablero);
            points.push_back(par);
            break;
        
        case 'B':
            len = 3;            
            par = can_it_place(len, tablero);
            points.push_back(par);
            break;
        
        case 'S':
            len = 2;
            par = can_it_place(len, tablero);
            points.push_back(par);
            break;
        
        case 'T':
            len = 1;
            par = can_it_place(len, tablero);
            points.push_back(par);
            break;

        default:
            break;
    }
    for (auto it : points){
        std::cout << it << std::endl;
    }
}

void placement(std::string TOKEN)
{
    std::map<char, size_t> remaining_fleet = {
        {'A', 1},
        {'B', 2},
        {'S', 3},
        {'T', 4}
    };

    std::set<std::pair<std::pair<size_t,size_t>, bool>> tablero;
    
    std::map<char, size_t>::iterator itm;

    for (auto& itmap : remaining_fleet)
    {
        while (itmap.second != 0)
        {
            place_boat(itmap.first, tablero);
            itmap.second--;
        }
    }
}

char randchar()
{
    int r = randint(0,1);
    if (r == 0)
    {
        return 'V';
    } else 
    {
        return 'H';
    } 
}

void update(std::pair<std::pair<size_t,size_t>, bool>& point)
{
    point.first.first = randint(0,9);
    point.first.second = randint(0,9);
    point.second = true;
}

std::pair<std::pair<size_t,size_t>, bool> rand_point(std::set<std::pair<std::pair<size_t,size_t>, bool>> data)
{
    auto point_b = generate_point();
    
    while (true)
    {
        if (verify(data, point_b))
        {
            break;
        } else 
        {
            update(point_b);
        }
    } 
    return point_b;
}

bool verify(std::set<std::pair<std::pair<size_t,size_t>, bool>> data,
            std::pair<std::pair<size_t,size_t>, bool> point)
{
    return data.count(point) == 0;
}

std::pair<std::pair<size_t,size_t>, bool> generate_point()
{
    int a = randint(0,9);
    int b = randint(0,9);
    auto point = std::make_pair(a,b);
    return std::make_pair(point, true);
}

std::pair<std::pair<size_t,size_t>,char> can_it_place(int len, std::set<std::pair<std::pair<size_t,size_t>, bool>>& tablero)
{
    char direc;
    auto tabpoint = generate_point();
    while (true)
    {
        bool rangeX = tabpoint.first.second + len <= 10;
        bool rangeY = tabpoint.first.first + len <= 10;
        if (rangeX&&rangeY)
        {
            char direction = randchar();
            if (direction == 'H')
            {
                bool fits = true;
                for (int i = 0; i < len; ++i)
                {
                        auto ub = std::make_pair(tabpoint.first.first+i,tabpoint.first.second);
                        auto point_ver = std::make_pair(ub,true);
                        fits = fits && verify(tablero,point_ver);
                }  
                if (fits)
                {
                    std::cout << "H " << tabpoint << std::endl;
                    for (int i = 0; i < len; ++i)
                    {
                        auto ub = std::make_pair(tabpoint.first.first+i+1,tabpoint.first.second);
                        auto point_ver = std::make_pair(ub,true);
                        tablero.insert(point_ver);
                        if (tabpoint.first.second+1 <= 10)
                        {
                            auto ub = std::make_pair(tabpoint.first.first+i,tabpoint.first.second+1);
                            auto point_ver = std::make_pair(ub,true);
                            tablero.insert(point_ver);
                        }
                        if (tabpoint.first.second-1 <= 10)
                        {
                            auto ub = std::make_pair(tabpoint.first.first+i,tabpoint.first.second-1);
                            auto point_ver = std::make_pair(ub,true);
                            tablero.insert(point_ver);
                        }
                    }
                    break;
                }      

            } else if (direction == 'V') 
            {
                bool fits = true;
                for (int i = 0; i < len; ++i)
                {
                        auto ub = std::make_pair(tabpoint.first.first,tabpoint.first.second+i);
                        auto point_ver = std::make_pair(ub,true);
                        fits = fits && verify(tablero,point_ver);
                }  
                if (fits)
                {
                    std::cout << "V " << tabpoint << std::endl;
                    for (int i = 0; i < len; ++i)
                    {
                        auto ub = std::make_pair(tabpoint.first.first,tabpoint.first.second+i);
                        auto point_ver = std::make_pair(ub,true);
                        tablero.insert(point_ver);

                        if (tabpoint.first.first+1 <= 10)
                        {
                            auto ub = std::make_pair(tabpoint.first.first+1,tabpoint.first.second+i+1);
                            auto point_ver = std::make_pair(ub,true);
                            tablero.insert(point_ver);

                        }
                        if (tabpoint.first.first-1 <= 10)
                        {
                            auto ub = std::make_pair(tabpoint.first.first-1,tabpoint.first.second+i+1);
                            auto point_ver = std::make_pair(ub,true);
                            tablero.insert(point_ver);
                        }
                    }
                break;
                }
            } 
            else 
            {
                update(tabpoint);
            }
        update(tabpoint);
        }
    update(tabpoint);
    }
    
    auto par1 = tabpoint.first.first;
    auto par2 = tabpoint.first.second;
    auto final_pair = std::make_pair(par1,par2);
    return std::make_pair(final_pair,direc);
}

template<typename entero_t>
entero_t randint(entero_t first, entero_t last)
{
    std::random_device dev;
    std::mt19937 eng(dev());
    std::uniform_int_distribution<entero_t> dis(first, last);
    return dis(eng);
}
