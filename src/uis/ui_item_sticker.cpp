//
// Created by stefa on 4/22/2026.
//

#include "../../include/ui_item_sticker.h"

ui_item_sticker::ui_item_sticker(float x,float y,float width,float height,item *new_item) : ui_item_element(x,y,width,height) {
    this->internal_item = new_item;
}

ui_item_sticker::ui_item_sticker(const ui_item_sticker &other) : ui_item_element(other) {
    if (other.internal_item != nullptr) {
        this->internal_item = new item(*other.internal_item);
    } else {
        this->internal_item = nullptr;
    }
}