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
#include "chunk_loader.h"

#include "machine.h"
#include "furnace_prototype.h"
#include "game_session.h"

class event_handler {
protected:
    std::queue<event*> event_queue;
public:
    virtual void process_events(sf::RenderWindow& window,graphic_engine &graphic_engine,game_session& session);
    void add_event(event *event);
    void process_tick_events(sf::RenderWindow& window,graphic_engine &graphic_engine,build_system &build_system,chunk_loader &loader,player& player, machine_handler& machines);
};


#endif //OOP_EVENT_HANDLER_H