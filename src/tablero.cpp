//
// Created by Alejandro  Otero on 2019-11-29.
//

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "tablero.h"

tablero::tablero(sf::RenderWindow *window):_window(window) {
    game();
}

void tablero::game() {
    while (_window->isOpen()){
        sf::Event evento;
        while( _window->pollEvent(evento)){
            if(evento.type == sf::Event::Closed)
                _window->close();
        }
        _window->clear(sf::Color::Blue);
        dibujo();
        _window->display();
    }
}

void tablero::dibujo() {
    for(int i=0; i<10;i++){
        for(int j=0; j<10; j++){

        }
    }
    sf::RectangleShape rectangulo(sf::Vector2f(600,600));
    rectangulo.setPosition(250,150);
    rectangulo.setFillColor(sf::Color::White);
    _window->draw(rectangulo);
    //disparada
    //disparada, le diste
    //disparada, hundiste el barco
    //no has disparado
}