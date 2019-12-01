#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "funct.hpp"
#include "prettyprint.hpp"
#include "tablero.h"
#include "casillas.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(750,750),"Battleship");
    tablero game(&window,750,750,10,10);

    while (window.isOpen()){
        sf::Event evento;
        while( window.pollEvent(evento)){
            if(evento.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        game.dibujo();
        window.display();
    }

    std::ifstream archivo("texto.txt");
    auto valores = read(archivo);
    parse(valores);
}
