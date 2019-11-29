#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include <optional>
#include <regex>
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


void parse(std::map<std::string,std::string> data)
{
    bool accepted = false;
    std::string TOKEN;
    for (auto& it : data)
    {
        if (it.first == "SCOPE")
        {
            //poner tamños;
        } 
        else if (it.first == "STATUS")
        {
            accepted = true;
        } 
        else if (it.first == "TOKEN")
        {
            TOKEN = it.second;
            std::cout << TOKEN << std::endl;
        }
    }
}
void placeFleet(){

}


void handshake(std::string name)
{
    std::ofstream archivo;
    archivo << "HANDSHAKE=" << name << std::endl;
    archivo.close();
}


/*
std::optional<std::ofstream> file_exists(std::regex r)
{
    
    auto path = std::filesystem::current_path() / "test";
    std::cout << path << std::endl;

    while (true)
    {
        std::cout << "Running again" << std::endl;
        auto it = std::filesystem::directory_iterator(path);
        auto count = std::distance(it, std::filesystem::directory_iterator());
        auto path = std::filesystem::current_path() / "test";
    std::cout << path << std::endl;

    while (true)
    {
        std::cout << "Running again" << std::endl;
        auto it = std::filesystem::directory_iterator(path);
        auto count = std::distance(it, std::filesystem::directory_iterator());
        // auto count = std::count_if(it, std::filesystem::directory_iterator(),
        //                            [](auto v) {
        //                                return true;
        //                            });
        if (count > 0)
        {
            for (it = std::filesystem::directory_iterator(path); it != std::filesystem::directory_iterator();)
            {
                std::filesystem::remove(*it);
                it++;
            }
            notify();
        }
    }
  
}
  */

bool verify()
{
    
}