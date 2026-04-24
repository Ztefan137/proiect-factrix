//
// Created by stefa on 4/13/2026.
//

#include "ui_item_tile.h"

#include <iostream>

ui_item_tile::ui_item_tile(float x,float y,float width,float height,item *new_item) : ui_item_element(x,y,width,height) {
    this->internal_item = new_item;
}
