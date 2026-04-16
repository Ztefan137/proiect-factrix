//
// Created by stefa on 4/16/2026.
//

#include "build_system.h"

#include <iostream>

build_system::build_system(chunk_loader &loader) : loader(loader){

}

std::string build_system::get_item() {
    return this->item;
}

bool build_system::get_on() {
    return this->on;
}

void build_system::set_item(std::string item) {
    this->item = item;
}

void build_system::set_on(bool on) {
    this->on = on;
}

bool build_system::can_build() {
    return true;
}

void build_system::set_mouse_tiles(int x, int y) {
    this->mouse_tile_x=x;
    this->mouse_tile_y=y;
}
