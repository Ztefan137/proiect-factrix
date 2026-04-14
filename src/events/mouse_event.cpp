//
// Created by stefa on 4/14/2026.
//

#include "mouse_event.h"

mouse_event::mouse_event(float mouse_x,float mouse_y) {
    this->mouse_x = mouse_x;
    this->mouse_y = mouse_y;
}

float mouse_event::get_mouse_x() {
    return mouse_x;
}

float mouse_event::get_mouse_y() {
    return mouse_y;
}
