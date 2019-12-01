//
// Created by Alejandro  Otero on 2019-11-29.
//

#include <SFML/Window/Event.hpp>
#include "tablero.h"

tablero::tablero(sf::RenderWindow *window, float h, float w, size_t r, size_t c):_window(window), height(h), width(w), rows(r), cols(c){
    game();
    float hc = height / rows;
    float wc = width / cols;
    casillas.resize(rows);
    for (auto &row: casillas)
        for (int i = 0; i < cols; i++) {
            row.emplace_back(hc, wc);
        }
}

void tablero::game() {

}

void tablero::dibujo() {
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            draw(
                    casillas[i][j].get_width()*i,
                    casillas[i][j].get_height()*j,
                    casillas[i][j].get_width(),
                    casillas[i][j].get_height()
                    );
        }
    }
}

    //disparada
    //disparada, le diste
    //disparada, hundiste el barco
    //no has disparado

void tablero::draw(float x, float y, float tam_x, float tam_y) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(tam_x, tam_y));
    rectangle.setPosition(x, y);
    rectangle.setOutlineThickness(1);
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setOutlineColor(sf::Color::Yellow);
    _window->draw(rectangle);
}
