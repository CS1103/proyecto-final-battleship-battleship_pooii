//
// Created by Alejandro  Otero on 2019-11-29.
//

#ifndef PROYECTO_FINAL_BATTLESHIP_BATTLESHIP_POOII_TABLERO_H
#define PROYECTO_FINAL_BATTLESHIP_BATTLESHIP_POOII_TABLERO_H

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <vector>


class tablero: public sf::Drawable, public sf::Transformable {
    sf::RenderWindow *_window;
    sf::VertexArray _vertices;
    sf::Texture _tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        states.transform*=getTransform();
        states.texture = &_tileset;
        target.draw(_vertices,states);
    }

public:
    tablero(sf::RenderWindow *window);
    void game();
    void dibujo();
    bool load();
};


#endif //PROYECTO_FINAL_BATTLESHIP_BATTLESHIP_POOII_TABLERO_H
