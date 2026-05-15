//
// Created by stefa on 5/15/2026.
//

#ifndef OOP_GAME_SESSION_EVENT_HANDLER_H
#define OOP_GAME_SESSION_EVENT_HANDLER_H
#include "event_handler.h"


class game_session_event_handler :public event_handler{
public:
    game_session_event_handler();
    void process_event(sf::RenderWindow &window, graphic_engine &graphic_engine, game_session &session);

};


#endif //OOP_GAME_SESSION_EVENT_HANDLER_H