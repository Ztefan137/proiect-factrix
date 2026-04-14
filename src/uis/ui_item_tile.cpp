//
// Created by stefa on 4/13/2026.
//

#include "ui_item_tile.h"

#include <iostream>

ui_item_tile::ui_item_tile(float x,float y,float width,float height,item *new_item) : ui(x,y,width,height) {
    this->internal_item = new_item;
}

void ui_item_tile::bind_data(ui_binder *binder) {
    //this->internal_item = binder->get<item>(this->bind_string);
}

void ui_item_tile::set_item(item * new_item) {
    this->internal_item = new_item;
}

item* ui_item_tile::get_item() const{
    return this->internal_item;
}
