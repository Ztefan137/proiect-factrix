//
// Created by stefa on 4/12/2026.
//

#include "../include/player.h"

player::player(float x, float y) {
    this->x = x;
    this->y = y;
    this->inventory.resize(50);
    this->add_item("iron_ore",110);
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

void player::add_item(std::string type, int count) {
    const int stack_size = 100;
    for (auto &it : inventory) {
        if (it.get_name() == type) {
            int space = stack_size - it.get_quantity();
            if (space > 0) {
                int to_add = std::min(space, count);
                it.add_quantity(to_add);
                count -= to_add;
            }
        }
        if (count <= 0) return;
    }

    if (count > 0) {
        for (auto &it : inventory) {
            if (it.get_name() == "") { // Check for an empty slot
                int to_add = std::min(stack_size, count);

                // Assuming your item class has a way to set these values
                // If you don't have a 'set' method, you might need:
                it = item(type, to_add);

                count -= to_add;
            }
            if (count <= 0) return;
        }
    }
}