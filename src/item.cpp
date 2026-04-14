//
// Created by stefa on 4/13/2026.
//

#include "../include/item.h"

item::item(std::string name, int quantity) {
    this->name = name;
    this->quantity = quantity;
}

std::string item::get_name() {
    return this->name;
}

int item::get_quantity() {
    return this->quantity;
}
