//
// Created by stefa on 4/12/2026.
//

#include "../include/player.h"

#include "../include/collision_handler.h"

player::player(float x, float y){
    this->x = x;
    this->y = y;
    this->inventory.resize(70);
    this->add_item("iron_ore",110);
    this->add_item("iron_plate",1);
    internal_crafter.bind_items(&inventory);
    internal_crafter.init_recipes("assets/configuration files/recipes_config.txt");

    this->crafting_grid.resize(70);
    this->crafting_grid[0]={"iron_plate",1};
    this->crafting_grid[1]={"furnace",1};
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

item* player::get_crafting_grid() {
    return this->crafting_grid.data();
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

void player::remove_item(std::string type, int count) {
    for (auto it = inventory.begin(); it != inventory.end() && count > 0; ) {
        if (it->get_name() == type) {
            int qty = it->get_quantity();
            if (qty <= count) {
                count -= qty;
                it = inventory.erase(it);
            } else {
                it->add_quantity(-count);
                count = 0;
                ++it;
            }
        } else {
            ++it;
        }
    }
}

bool player::has_item(std::string type) {
    for (const auto &it : this->inventory) {
        if (it.get_name() == type && it.get_quantity() > 0) {
            return true;
        }
    }
    return false;
}


void player::mine(float dp) {
    this->mining_progress+=dp;
}

bool player::has_mined() {
    if (this->mining_progress > 1) {
        this->mining_progress = 0;
        return true;
    }
    return false;
}

void player::update() {
    this->internal_crafter.craft();
}

void player::craft(item item) {
    this->internal_crafter.init_craft(item);
}
