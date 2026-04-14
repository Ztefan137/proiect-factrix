//
// Created by stefa on 4/12/2026.
//

#include "../include/player.h"

player::player(float x, float y) {
    this->x = x;
    this->y = y;
    this->inventory.reserve(50);
    item some_item("test_item",10);
    this->inventory.push_back(some_item);
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

item* player::get_inventory() {
    return this->inventory.data();
}
