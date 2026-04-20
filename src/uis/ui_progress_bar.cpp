//
// Created by stefa on 4/19/2026.
//

#include "ui_progress_bar.h"

ui_progress_bar::ui_progress_bar(float x, float y, float width, float height,sf::Color color) : ui(x,y,width,height), color(color){
}

void ui_progress_bar::reset() {
    this->progress=0.f;
}

void ui_progress_bar::advance_progress(float d_progress) {
    this->progress += d_progress;
}

float ui_progress_bar::get_progress() const{
    return this->progress;
}

sf::Color ui_progress_bar::get_color() const{
    return this->color;
}
