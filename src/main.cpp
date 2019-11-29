#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>

#include "funct.hpp"
#include "prettyprint.hpp"

int main()
{
    // First we do the handshake

    size_t token;
    // std::pair<size_t, size_t> scope;

    // TODO: Probably factorize this to a function returning a size_t (the
    //       token).
    size_t try_number = 0;
    while (true)
    {
        std::string team_name = "TeamA-";

        handshake_write(team_name + std::to_string(try_number));

        std::regex file_regex("^\\w+\\.out$");
        std::optional<std::ifstream> file_in;
        // TODO: Here we wait til we get a response in 'Player.out' or something
        while (file_in.has_value())
        {
            file_in = open_file(file_regex);
        }

        auto parts = read(file_in.value());

        if (parts["STATUS"] != "ACCEPTED")
        {
            try_number++;
        }
    }
}
