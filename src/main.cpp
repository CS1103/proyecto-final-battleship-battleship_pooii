#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <regex>
#include <stack>
#include <string>
#include <utility>

#include "funct.hpp"
#include "prettyprint.hpp"

int main()
{
    std::regex server_out_regex("^\\w+\\.out$");
    std::optional<std::ifstream> server_out_file;

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

        while (!server_out_file.has_value())
        {
            server_out_file = open_file(server_out_regex);
        }

        auto parts = read(server_out_file.value());

        if (parts.find("STATUS")->second == "REJECTED")
        {
            try_number++;
        }
    }

    // Second: Position the fleet
    std::map<size_t, size_t> remaining_fleet = {
        {1, 4},
        {2, 3},
        {3, 2},
        {4, 1}
    };

    // TODO: Fleet placement.

    // Third: Start attacking

    // Fill all the remaining positions to attack, they are in a set so that we
    // can check rapidly wheter a specific position was already attacked.
    std::set<std::pair<size_t, size_t>> pos_left_to_shoot;
    for (size_t i = 0; i < scope.first; i++)
    {
        for (size_t j = 0; j < scope.second; j++)
        {
            pos_left_to_shoot.emplace(i, j);
        }
    }

    std::random_device rd;
    server_out_file.reset();
    while (!pos_left_to_shoot.empty())
    {
        // Select a position not yet shot
        auto it_pos_to_shoot = std::next(pos_left_to_shoot.begin(),
                                         rd() % pos_left_to_shoot.size());
        auto pos_to_shoot = *it_pos_to_shoot;

        attack_position(pos_to_shoot.first, pos_to_shoot.second, token);

        while (!server_out_file.has_value())
        {
            server_out_file = open_file(server_out_regex);
        }
        auto parts = read(server_out_file.value());
        server_out_file.reset();

        if (parts.find("STATUS")->second == "REJECTED")
        {
            continue;
        }
        pos_left_to_shoot.erase(it_pos_to_shoot);

        auto message = parts.find("MESSAGE")->second;
        if (message == "WINNER")
        {
            std::cout << "You won!" << std::endl;
            return 0;
        }
        if (message == "GAMEOVER")
        {
            std::cout << "You lost!" << std::endl;
            return 0;
        }

        if (message == "FAILED")
        {
            continue;
        }

        // If we get here, our shot was a hit.

        std::stack<std::pair<std::pair<size_t, size_t>,
                            std::pair<size_t, size_t>>>
            adjacent_pos_dir;

        for (auto& pd : adjacent_positions(pos_to_shoot,
                                            scope.first, scope.second))
        {
            adjacent_pos_dir.push(pd);
        }

        while (!adjacent_pos_dir.empty())
        {
            std::pair<size_t, size_t> pos;
            std::pair<size_t, size_t> move_direction;
            std::tie(pos, move_direction) = adjacent_pos_dir.top();

            attack_position(pos.first, pos.second, token);

            auto parts = read(server_out_file.value());

            if (parts.find("STATUS")->second == "REJECTED")
            {
                continue;
            }
            adjacent_pos_dir.pop();

            auto message = parts.find("MESSAGE")->second;
            if (message == "WINNER")
            {
                std::cout << "You won!" << std::endl;
                return 0;
            }
            if (message == "GAMEOVER")
            {
                std::cout << "You lost!" << std::endl;
                return 0;
            }
            else if (message == "FAILED")
            {
                continue;
            }
            else
            {
                auto new_pos = std::make_pair(pos.first + move_direction.first,
                                              pos.second + move_direction.second);
                if (is_inside_map(new_pos, scope))
                {
                    adjacent_pos_dir.emplace(new_pos, move_direction);
                }
            }
        }
    }
}
