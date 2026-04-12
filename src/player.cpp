//
// Created by stefa on 4/12/2026.
//

#include "../include/player.h"

player::player(float x, float y) {
    this->x = x;
    this->y = y;
}

void player::move(float dx, float dy) {
    this->x += dx;
    this->y += dy;
}

float player::get_x() {
    return this->x;
}
float player::get_y() {
    return this->y;
}
