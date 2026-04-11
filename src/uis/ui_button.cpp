//
// Created by stefa on 4/4/2026.
//

#include "ui_button.h"
#include <string>

ui_button::ui_button(float x, float y, float width, float height, std::string text) : ui(x,y,width,height){
    this->text = text;
}

std::string ui_button::get_string() const {
    return this->text;
}
