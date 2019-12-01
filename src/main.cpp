#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <stdio.h> 
#include <stdlib.h> 
#include <string>
#include <time.h>
#include <utility>

#include "funct.hpp"
#include "prettyprint.hpp"

int main()
{
    std::regex server_out_regex("^\\w+\\.out$");
    std::optional<std::ifstream> server_out_file;
/*
    // First: Do the handshake.

    size_t token;
    // We assume that the size will always be 10x10.
    std::pair<size_t, size_t> scope = {10, 10};

    // TODO: Probably factorize this to a function returning a size_t (the
    //       token)
    size_t try_number = 0;
    while (true)
    {
        std::string team_name = "TeamA-";

        handshake_write(team_name + std::to_string(try_number));

        // TODO: Here we wait til we get a response in 'Player.out' or something
        while (!server_out_file.has_value())
        {
            server_out_file = open_file(server_out_regex);
        }

        auto parts = read(server_out_file.value());

        if (parts["STATUS"] != "ACCEPTED")
        {
            try_number++;
        }1
    // TODO: Fleet placement.

    // Third: Start attacking

    // Fill all the remaining positions to attack.
    std::set<std::pair<size_t, size_t>> pos_left_to_shoot;
    for (size_t i = 0; i < scope.first; i++)
    {
        for (size_t j = 0; j < scope.second; j++)
        {
            pos_left_to_shoot.emplace(i, j);
        }
    }

    while (!pos_left_to_shoot.empty())
    {
        auto n_remaining = pos_left_to_shoot.size();
    }
*/
    server_out_file.reset();
    std::ofstream archivoooo;
    auto pair1 =  std::make_pair(1,1);
    auto pair2 = std::make_pair(pair1,true);

    auto pair3 =  std::make_pair(1,4);
    auto pair4 = std::make_pair(pair3,true);

    auto pair5 =  std::make_pair(2,1);
    auto pair6 = std::make_pair(pair5,true);

    std::set<std::pair<std::pair<size_t,size_t>, bool>> data;
    data.insert(pair2);
    data.insert(pair4);
    data.insert(pair6);

    placement(3,"1234");

    auto it = data.begin();
    auto parthing = rand_point(data);
}
