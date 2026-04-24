//
// Created by stefa on 4/22/2026.
//

#include "../../include/ui_item_element.h"

ui_item_element::ui_item_element(float x, float y, float width, float height, item *new_item) : ui(x,y,width,height),internal_item(new_item){

}

void ui_item_element::bind_data(ui_binder *binder) {
    this->internal_item = binder->get<item>(this->bind_string);
}

void ui_item_element::set_item(item * new_item) {
    this->internal_item = new_item;
}

item* ui_item_element::get_item() const{
    return this->internal_item;
}
