//
// Created by stefa on 3/13/2026.
//

#include "../../include/ui.h"
#include <SFML/Graphics.hpp>
#include "ui_style.h"
#include <iostream>

ui::ui() {
    this->x=0;
    this->y=0;
    this->width=0;
    this->height=0;
    this->visibility=false;
}

ui::ui(float x, float y, float width, float height){
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
    this->visibility=false;
}

ui::~ui() {
    for (const auto* sub_ui : this->sub_uis) {
        delete sub_ui;
    }
}

void ui::set_type(std::string type) {
    this->ui_type=type;
}

void ui::set_style(ui_style new_ui_style){
    this->internal_ui_style=new_ui_style;
    for (auto* sub_ui:sub_uis) {
        sub_ui->set_style(new_ui_style);
    }
}

void ui::set_visibility(bool new_visibility) {
    this->visibility=new_visibility;
}

void ui::add_sub_ui(ui* new_sub_ui) {
    this->sub_uis.push_back(new_sub_ui);
}
void ui::render(sf::RenderWindow& window) const{
    std::vector<const ui*> to_render;
    to_render.push_back(this);
    while (!to_render.empty()) {
        const ui* current = to_render.back();
        to_render.pop_back();
        current->render_self(window);
        for (const auto* sub_ui : current->sub_uis) {
            to_render.push_back(sub_ui);
        }
    }
}
void ui::render_self(sf::RenderWindow& window) const{
    this->internal_ui_style.render(this->ui_type,window,this);
}
float ui::get_x() const {
    return this->x;
}
float ui::get_y() const {
    return this->y;
}
float ui::get_width() const {
    return this->width;
}
float ui::get_height() const {
    return this->height;
}
bool ui::get_visibility() const {
    return this->visibility;
}

void ui::hide() {
    this->visibility=false;
}
void ui::show() {
    this->visibility=true;
}

