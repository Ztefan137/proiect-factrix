//
// Created by stefa on 4/6/2026.
//

#ifndef OOP_EVENT_HANDLER_H
#define OOP_EVENT_HANDLER_H

#include <queue>
#include <SFML/Graphics.hpp>

#include "player.h"
#include "generic_event.h"
#include "graphic_engine.h"

class event_handler {
    std::queue<event*> event_queue;
public:
    void process_events(sf::RenderWindow& window,graphic_engine &graphic_engine,player& player);
};


#endif //OOP_EVENT_HANDLER_H