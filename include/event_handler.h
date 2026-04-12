//
// Created by stefa on 4/6/2026.
//

#ifndef OOP_EVENT_HANDLER_H
#define OOP_EVENT_HANDLER_H

#include <SFML/Graphics.hpp>

#include "graphic_engine.h"
#include "player.h"

class event_handler {
public:
    void process_events(sf::RenderWindow& window,graphic_engine &graphic_engine,player& player);
};


#endif //OOP_EVENT_HANDLER_H