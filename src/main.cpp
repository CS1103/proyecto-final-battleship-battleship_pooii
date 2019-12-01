#include <iostream>

#include "Player.hpp"
#include "prettyprint.hpp"

int main()
{
    Player p("TeamA");
    if (p.play())
    {
        std::cout << "You won" << std::endl;
    }
    else
    {
        std::cout << "You lost" << std::endl;
    }
}
