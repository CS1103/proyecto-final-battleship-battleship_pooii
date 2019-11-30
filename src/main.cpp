#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "funct.hpp"
#include "prettyprint.hpp"
#include "tablero.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(900,700),"Battleship");
    tablero game(&window);
    std::ifstream archivo("texto.txt");
    auto valores = read(archivo);
    parse(valores);
    
}
