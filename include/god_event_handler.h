//
// Created by stefa on 5/15/2026.
//

#ifndef OOP_GOD_EVENT_HANDLER_H
#define OOP_GOD_EVENT_HANDLER_H
#include "event_handler.h"


class god_event_handler : public event_handler{
public:
    god_event_handler();
    void process_events(sf::RenderWindow &window, graphic_engine &graphic_engine, game_session &session) override;
};


#endif //OOP_GOD_EVENT_HANDLER_H