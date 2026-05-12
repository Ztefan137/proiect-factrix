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
