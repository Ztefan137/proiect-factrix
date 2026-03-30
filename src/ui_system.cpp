//
// Created by stefa on 3/29/2026.
//

#include "ui_system.h"
#include <SFML/Graphics.hpp>
#include <string>

void ui_system::add_ui(ui &ui) {
    this->ui_list.push_back(ui);
}

void ui_system::render_uis(sf::RenderWindow& window) {
    for (auto &ui : this->ui_list) {
        ui.render(window);
    }
}

void ui_system::configure_uis(std::string config_xml) {
    if (config_xml == "default") {

        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        const auto screenWidth = static_cast<float>(desktop.size.x);
        const auto screenHeight = static_cast<float>(desktop.size.y);

        ui test_ui(screenWidth/2,screenHeight/2,50,50);
        this->add_ui(test_ui);
    }
}
