//
// Created by stefa on 3/13/2026.
//

#include "../include/ui.h"
#include <cmath>
#include "graphic_functions.h"
#include <SFML/Graphics.hpp>

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
void ui::render(sf::RenderWindow &window) {
    rect(window,this->x-floor(this->width/2),this->y-floor(this->height/2),this->x+floor(this->width/2),this->y+floor(this->height/2),sf::Color::Black);
    for (auto &sub_ui : sub_uis) {
        sub_ui.render(window);
    }
}
