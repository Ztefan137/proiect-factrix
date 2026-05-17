//
// Created by stefa on 5/13/2026.
//

#ifndef OOP_INTERFACE_LAYER_H
#define OOP_INTERFACE_LAYER_H
#include <SFML/Graphics.hpp>

#include "event_handler.h"
#include "game_session.h"
#include "graphic_engine.h"
class interface_layer {
    game_session& session;
    sf::RenderWindow window;
    graphic_engine g_engine;
    event_handler handler;

public:
    interface_layer(game_session&);
    void process_input(std::string time_step);
    void process_output();
    bool is_open();
    void init();
};


#endif //OOP_INTERFACE_LAYER_H