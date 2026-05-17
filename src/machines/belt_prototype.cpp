//
// Created by stefa on 5/10/2026.
//

#include "belt_prototype.h"

#include <iostream>

belt_prototype::belt_prototype() : curr_item("",0), cached_item("",0){

}

void belt_prototype::update() {

}
void belt_prototype::cache_items() {
    this->cached_item=this->curr_item;
}

void belt_prototype::move_items(belt_prototype* back,belt_prototype* left,belt_prototype* right) {
    if (left) {
        this->curr_item=left->cached_item;
    }
    if (right) {
        this->curr_item=right->cached_item;
    }
    if (back) {
        this->curr_item=back->cached_item;
    }
}

item belt_prototype::get_cached() {
    return this->cached_item;
}

void belt_prototype::place_item(item item) {
    std::cout<<"placing item"<<item.get_name()<<"\n";
    this->curr_item=item;
}

std::ostream& operator<<(std::ostream &os, const belt_prototype &belt) {
    os << belt.curr_item.get_name() << " " << belt.curr_item.get_quantity() << "\n";
    os << belt.cached_item.get_name() << " " << belt.cached_item.get_quantity() << "\n";
    return os;
}

std::istream& operator>>(std::istream &is, belt_prototype &belt) {
    std::string curr_name;
    int curr_quantity;
    std::string cached_name;
    int cached_quantity;
    is >> curr_name >> curr_quantity >> cached_name >> cached_quantity;
    belt.curr_item={curr_name,curr_quantity};
    belt.cached_item={cached_name,cached_quantity};
    return is;
}