//
// Created by Alejandro  Otero on 2019-11-30.
//

#ifndef PROYECTO_FINAL_BATTLESHIP_BATTLESHIP_POOII_CASILLAS_H
#define PROYECTO_FINAL_BATTLESHIP_BATTLESHIP_POOII_CASILLAS_H

#include <iostream>

using namespace std;

class casilla {
    float width;
    float height;
public:
    casilla(float w, float h);

    float get_width();

    float get_height();
};


#endif //PROYECTO_FINAL_BATTLESHIP_BATTLESHIP_POOII_CASILLAS_H
