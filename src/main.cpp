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


    // Second: Position the fleet
    std::map<size_t, size_t> remaining_fleet = {
        {1, 4},
        {2, 3},
        {3, 2},
        {4, 1}
    };

    // TODO: Fleet placement.

    // Third: Start attacking


}
