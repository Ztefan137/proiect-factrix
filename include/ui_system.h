//
// Created by stefa on 3/29/2026.
//

#ifndef OOP_UI_SYSTEM_H
#define OOP_UI_SYSTEM_H
#include <vector>
#include "ui.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "event.h"
#include <queue>

class ui_system {
    std::vector<ui*> ui_list;
public:
    ~ui_system();
    void add_ui(ui* ui);
    void render_uis(sf::RenderWindow& window);
    void configure_uis(std::string config_xml);
    void process_event(event* processed_event,std::queue<event*>* event_queue);
};


#endif //OOP_UI_SYSTEM_H