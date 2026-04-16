//
// Created by stefa on 4/16/2026.
//

#ifndef OOP_ACTION_HANDLER_H
#define OOP_ACTION_HANDLER_H
#include <map>
#include "string"
#include <queue>
#include "event.h"

class action_handler {
    std::map<std::string,void(*)(std::queue<event*>* event_queue,std::string)> item_actions;
    std::map<std::string,void(*)(std::queue<event*>* event_queue)> button_actions;
public:
    void add_item_action(std::string name,void(*)(std::queue<event*>* event_queue,std::string));
    void add_button_action(std::string name,void(*)(std::queue<event*>* event_queue));
    void call_item(std::string name,std::queue<event*>* event_queue,std::string item);
    void call_button(std::string name,std::queue<event*>* event_queue);
};


#endif //OOP_ACTION_HANDLER_H