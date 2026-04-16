//
// Created by stefa on 3/29/2026.
//

#include "ui_system.h"
#include <SFML/Graphics.hpp>
#include <string>

#include "ui_render_functions.h"
#include "ui_style.h"

#include "ui_section.h"
#include "ui_window.h"
#include "ui.h"
#include "ui_button.h"
#include "ui_item_tile.h"

#include <fstream>

#include <iostream>

#include "../include/action_handler.h"
#include "../include/ui_constructor.h"

#include "event.h"
#include "key_event.h"
#include "mouse_event.h"
#include "structures.h"
#include "ui_event.h"
#include "ui_actions.h"

ui_system::~ui_system() {
    for (ui* element : this->ui_list) {
        delete element;
    }
}

void ui_system::add_ui(ui* ui) {
    this->ui_list.push_back(ui);
}


void ui_system::render_uis(sf::RenderWindow& window) {
    for (auto &ui : this->ui_list) {
        if (ui->get_visibility()) {
            ui->render(window);
        }
    }
}

void ui_system::configure_uis(std::string config_xml) {
    ui_style default_style;
    default_style.set_function("ui",ui_render_style_test1);
    default_style.set_function("window",window_render_style_style1_opaque);
    default_style.set_function("section",section_render_style_style1_opaque);
    default_style.set_function("item_tile",item_tile_render_style_style1_opaque);
    default_style.set_function("item_tile_grid",item_tile_grid_render_style_style1_opaque);\

    action_handler default_handler;
    default_handler.add_item_action("build_mode",open_build_mode);
    if (config_xml == "default") {

        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        const auto screenWidth = static_cast<float>(desktop.size.x);
        const auto screenHeight = static_cast<float>(desktop.size.y);
        ui* test_window = new ui_window(screenWidth/2,screenHeight/2,1800,1200,"Test window");
        test_window->set_style(default_style);
        test_window->set_type("window");
        test_window->show();
        test_window->hide();

        ui* test_section = new ui_section(screenWidth/2,screenHeight/2+25,1100,500,"Test section",true);
        test_section->set_style(default_style);
        test_section->set_type("section");

        ui* test_item_tile = new ui_item_tile(screenWidth/2,screenHeight/2+25,100,100);
        test_item_tile->set_style(default_style);
        test_item_tile->set_type("item_tile");
        test_section->add_sub_ui(test_item_tile);

        test_window->add_sub_ui(test_section);

        this->add_ui(test_window);
        //this->add_ui(test_section);
    }else {
        std::cout<<"configurating uis"<<std::endl;
        ui_constructor default_constructor;
        std::vector<ui*> constructed_uis=default_constructor.construct_from_xml(config_xml);
        for (ui* element : constructed_uis) {
            std::cout<<"configuring uis"<<std::endl;
            element->set_style(default_style);
            element->set_actions(default_handler);
            this->add_ui(element);
        }
        std::cout<<this->ui_list.size()<<std::endl;
    }
}
void ui_system::process_event(event* processed_event,std::queue<event*>* event_queue){
    if (auto* ke = dynamic_cast<key_event*>(processed_event)) {
        if (ke->get_key() == "e") {
            this->ui_list[0]->set_visibility(!this->ui_list[0]->get_visibility());
        }
    }else if (auto* me = dynamic_cast<mouse_event*>(processed_event)) {
        for (auto &ui:this->ui_list) {
            if (!ui->get_visibility())
                continue;
            ui->check_click(me->get_mouse_x(),me->get_mouse_y(),event_queue);
        }
    }else if (auto* uoe = dynamic_cast<ui_event*>(processed_event)) {
        this->ui_list[uoe->get_index()]->bind(uoe->get_binder());
    }
}
