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
//pick a point and try either vertical or horizontal (rndm)
//if not work, try next point in diagonal
//                   A,B,S,T                                  X , Y         FALSE  (true si usado)                        

void place_boat(char type_ship, std::set<std::pair<std::pair<size_t,size_t>, bool>>& tablero)
{   
    int len;
    switch (type_ship)
    {
        case 'A':
            len = 1;
            canItPlace(len, tablero);
        break;
        
        case 'B':
            len = 3;
            canItPlace(len, tablero);
        break;
        
        case 'S':
            len = 2;
            canItPlace(len, tablero);
        break;
        
        case 'T':
            len = 1;
            canItPlace(len, tablero);
        break;
        default:
            std::cout<<"no"<<std::endl;
    }
}

//std::ofstream 

void placement(int accepted, std::string TOKEN)
{
    std::map<char, size_t> remaining_fleet = {
        {'A', 1},
        {'B', 2},
        {'S', 3},
        {'T', 4}
    };

    std::set<std::pair<std::pair<size_t,size_t>, bool>> tablero;
    
    std::map<char, size_t>::iterator itm;

    for (auto& itmap : remaining_fleet){
        while(itmap.second != 0){
            place_boat(itmap.first,tablero);
            itmap.second--;
        }
    }

/*
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
*/    
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
    auto point_b = generateP();
    
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

std::pair<std::pair<size_t,size_t>, bool> generateP()
{
    int a = randint(0,9);
    int b = randint(0,9);
    auto point = std::make_pair(a,b);
    return std::make_pair(point, true);
}

std::pair<size_t, size_t> canItPlace(int len, std::set<std::pair<std::pair<size_t,size_t>, bool>>& tablero)
{
    auto tabpoint = generateP();
    while (true)
    {
        bool rangeX = tabpoint.first.second + len <= 10;
        bool rangeY = tabpoint.first.first + len <= 10;
        if(rangeX&&rangeY){
            char direction = randchar();
            if (direction == 'H')
            {
                bool fits = true;
                for(int i = 0; i < len; ++i)
                {
                        auto ub = std::make_pair(tabpoint.first.first+i,tabpoint.first.second);
                        auto point_ver = std::make_pair(ub,true);
                        fits = fits && verify(tablero,point_ver);
                }  
                if (fits)
                {
                    std::cout << "H " << tabpoint << std::endl;
                    for(int i = 0; i < len; ++i)
                    {
                        auto ub = std::make_pair(tabpoint.first.first+i,tabpoint.first.second);
                        auto point_ver = std::make_pair(ub,true);
                        tablero.insert(point_ver);
                    }
                    break;
                }      

            } else if (direction == 'V') 
            {
                bool fits = true;
                for(int i = 0; i < len; ++i)
                {
                        auto ub = std::make_pair(tabpoint.first.first,tabpoint.first.second+i);
                        auto point_ver = std::make_pair(ub,true);
                        fits = fits && verify(tablero,point_ver);
                }  
                if (fits)
                {
                    std::cout << "V " << tabpoint << std::endl;
                    for(int i = 0; i < len; ++i)
                    {
                        auto ub = std::make_pair(tabpoint.first.first,tabpoint.first.second+i);
                        auto point_ver = std::make_pair(ub,true);
                        tablero.insert(point_ver);
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
}



template<typename entero_t>
entero_t randint(entero_t first, entero_t last) {
  std::random_device dev;
  std::mt19937 eng(dev());
  std::uniform_int_distribution<entero_t> dis(first, last);
  return dis(eng);
}