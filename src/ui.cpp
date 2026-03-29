//
// Created by stefa on 3/13/2026.
//

#include "../include/ui.h"

ui::ui() {
    this->x=0;
    this->y=0;
    this->width=0;
    this->height=0;
    this->visibility=false;
}

ui::ui(float x, float y, float width, float height) {
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
    this->visibility=false;
}

void ui::add_sub_ui(const ui& new_sub_ui) {
    this->sub_uis.push_back(new_sub_ui);
}
