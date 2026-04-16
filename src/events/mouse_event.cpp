//
// Created by stefa on 4/14/2026.
//

#include "mouse_event.h"

mouse_event::mouse_event(float mouse_x, float mouse_y, bool clicked, sf::View *view) {
    this->mouse_x = mouse_x;
    this->mouse_y = mouse_y;
    //this->clicked = clicked;
    this->view=view;
}

float mouse_event::get_mouse_x() {
    return mouse_x;
}

float mouse_event::get_mouse_y() {
    return mouse_y;
}

void mouse_event::set_view(sf::View *view) {
    this->view=view;
}

sf::View* mouse_event::get_view() {
    return this->view;
}
