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




#include <string>



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

