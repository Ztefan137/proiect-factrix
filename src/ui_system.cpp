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

#include <fstream>

#include <iostream>

#include "ui_constructor.h"

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
            this->add_ui(element);
        }
        std::cout<<this->ui_list.size()<<std::endl;
    }
}
