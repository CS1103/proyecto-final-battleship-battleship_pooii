//
// Created by Alejandro  Otero on 2019-11-29.
//

#ifndef PROYECTO_FINAL_BATTLESHIP_BATTLESHIP_POOII_TABLERO_H
#define PROYECTO_FINAL_BATTLESHIP_BATTLESHIP_POOII_TABLERO_H

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "casillas.h"

using namespace std;

class tablero{
    sf::RenderWindow *_window;
    size_t rows;
    size_t cols;
    float width;
    float height;
    vector<vector<casilla>> casillas;

    void draw(float x, float y, float tam_x, float tam_y);

public:
    tablero(sf::RenderWindow *window,float h, float w, size_t r, size_t c);
    void game();
    void dibujo();
};


#endif //PROYECTO_FINAL_BATTLESHIP_BATTLESHIP_POOII_TABLERO_H
