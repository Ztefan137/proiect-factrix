//
// Created by stefa on 4/13/2026.
//

#include "../include/item.h"

item::item(std::string name, int quantity){
    this->name = name;
    this->quantity = quantity;
}

std::string item::get_name() const {
    return this->name;
}

void item::set_name(std::string new_name) {
    this->name = new_name;
}

int item::get_quantity() const{
    return this->quantity;
}

void item::add_quantity(int d_quantity) {
    this->quantity += d_quantity;
}

void item::take_quantity(int d_quantity) {
    this->quantity -= d_quantity;
    if (this->quantity <= 0) {
        this->quantity = 0;
        this->name="";
    }
}
