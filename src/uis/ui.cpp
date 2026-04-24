//
// Created by stefa on 3/13/2026.
//

#include "../../include/ui.h"
#include <SFML/Graphics.hpp>
#include "ui_style.h"
#include <iostream>
#include "event.h"
#include "generic_event.h"
#include "queue"
#include "structures.h"
#include "ui_item_tile.h"

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
void ui::set_actions(action_handler new_action_handler) {
    this->internal_action_handler=new_action_handler;
    for (auto* sub_ui:sub_uis) {
        sub_ui->set_actions(new_action_handler);
    }
}


void ui::set_bind_string(std::string new_bind_string) {
    this->bind_string=new_bind_string;
}

void ui::set_visibility(bool new_visibility) {
    this->visibility=new_visibility;
}

void ui::add_sub_ui(ui* new_sub_ui) {
    this->sub_uis.push_back(new_sub_ui);
}
void ui::render(sf::RenderWindow& window){
    std::vector<ui*> to_render;
    to_render.push_back(this);
    while (!to_render.empty()) {
        ui* current = to_render.back();
        to_render.pop_back();
        current->render_self(window);
        for (auto* sub_ui : current->sub_uis) {
            to_render.push_back(sub_ui);
        }
    }
}
void ui::render_self(sf::RenderWindow& window){
    this->internal_ui_style.render(this->hovered?(this->ui_type+"_hover"):this->ui_type,window,this);
    this->hovered=false;
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

void ui::bind(ui_binder* binder){
    this->bind_data(binder);
    for (auto* sub_ui:sub_uis){
        if (this -> ui_type != "item_tile_grid") {
            sub_ui->bind(binder);
        }
    }
}

void ui::bind_data(ui_binder *binder) {
    ui_binder* github_actions_binder=binder;
    std::cout<<"bind";
}

bool ui::is_mouse_inside(float x_mouse, float y_mouse) {
    float half_w = this->width * 0.5f;
    float half_h = this->height * 0.5f;

    return x_mouse >= (this->x - half_w) && x_mouse <= (this->x + half_w) && y_mouse >= (this->y - half_h) && y_mouse <= (this->y + half_h);
}
void ui::check_click(float x_mouse,float y_mouse,std::queue<event*>* event_queue) {
    if (!this->is_mouse_inside(x_mouse, y_mouse))
        return;

    for (auto& ui : this->sub_uis) {
        if (ui->is_mouse_inside(x_mouse, y_mouse)) {
            ui->check_click(x_mouse, y_mouse,event_queue);
            return;
        }
    }
    std::cout << "Deepest UI element clicked: " << this->ui_type << "\n";
    if (this->action_string != "") {
        if (this->ui_type == "item_tile") {
            std::cout<<"Clicked item tile";
            this->internal_action_handler.call_item(this->action_string,event_queue,dynamic_cast<ui_item_tile*>(this)->get_item());
        }
        if (this->ui_type == "button") {
            std::cout<<"Clicked button";
            this->internal_action_handler.call_button(this->action_string,event_queue);
        }
    }
}

void ui::check_hover(float x_mouse, float y_mouse) {
    if (!this->is_mouse_inside(x_mouse, y_mouse))
        return;

    for (auto& ui : this->sub_uis) {
        if (ui->is_mouse_inside(x_mouse, y_mouse)) {
            ui->check_hover(x_mouse, y_mouse);
            return;
        }
    }
    if (this->ui_type == "item_tile"|| this->ui_type == "button") {
        this->hovered=true;
    }
}

void ui::set_action_string(std::string new_action_string) {
    this->action_string=new_action_string;
}
