//
// Created by Alejandro  Otero on 2019-11-30.
//

#include "casillas.h"

casilla::casilla(float h, float w):height(h),width(w) {}

float casilla::get_height() {
    return height;
}

float casilla::get_width() {
    return width;
}