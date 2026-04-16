//
// Created by stefa on 4/12/2026.
//

#include "../include/player.h"

#include "collision_handler.h"

player::player(float x, float y) {
    this->x = x;
    this->y = y;
    this->inventory.resize(50);
    this->add_item("iron_ore",110);
}

void player::move(float dx, float dy,chunk_loader &loader) {
    collision_handler collision_handler(loader);
    if(!collision_handler.is_collision(x+dx,y+dy)){
        this->x += dx;
        this->y += dy;
    }
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
            if (it.get_name() == "") {
                int to_add = std::min(stack_size, count);
                it = item(type, to_add);

                count -= to_add;
            }
            if (count <= 0) return;
        }
    }
}