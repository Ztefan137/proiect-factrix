//
// Created by stefa on 4/13/2026.
//

#include "ui_item_tile.h"

#include <iostream>

ui_item_tile::ui_item_tile(float x,float y,float width,float height,item *new_item) : ui_item_element(x,y,width,height) {
    this->internal_item = new_item;
}


ui_item_tile::ui_item_tile(const ui_item_tile &other) : ui_item_element(other) {
    if (other.internal_item != nullptr) {
        this->internal_item = new item(*other.internal_item);
    } else {
        this->internal_item = nullptr;
    }
}