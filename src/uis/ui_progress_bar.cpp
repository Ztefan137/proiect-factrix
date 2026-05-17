//
// Created by stefa on 4/19/2026.
//
#include <iostream>

#include "ui_progress_bar.h"

ui_progress_bar::ui_progress_bar(float x, float y, float width, float height,sf::Color color) : ui(x,y,width,height), color(color){
}

float ui_progress_bar::get_progress() const{
    return *this->progress;
}

sf::Color ui_progress_bar::get_color() const{
    return this->color;
}

void ui_progress_bar::bind_data(ui_binder *binder) {
    this->progress=binder->get<float>(this->bind_string);
}

ui_progress_bar::ui_progress_bar(const ui_progress_bar &other) : ui(other) {
    this->color = other.color;
    this->progress = other.progress;
}