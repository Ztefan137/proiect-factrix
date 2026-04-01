//
// Created by stefa on 3/29/2026.
//

#ifndef OOP_UI_SYSTEM_H
#define OOP_UI_SYSTEM_H
#include <vector>
#include "ui.h"
#include <SFML/Graphics.hpp>
#include <string>


class ui_system {
    std::vector<ui*> ui_list;
public:
    ~ui_system();
    void add_ui(ui* ui);
    void render_uis(sf::RenderWindow& window);
    void configure_uis(std::string config_xml);
};


#endif //OOP_UI_SYSTEM_H