//
// Created by stefa on 4/16/2026.
//

#ifndef OOP_ACTION_HANDLER_H
#define OOP_ACTION_HANDLER_H
#include <map>
#include "string"
#include <queue>
#include "event.h"
#include "item.h"

class action_handler {
    std::map<std::string,void(*)(std::queue<event*>*,item*)> item_actions;
    std::map<std::string,void(*)(std::queue<event*>*)> button_actions;
public:
    void add_item_action(std::string name,void(*)(std::queue<event*>*,item*));
    void add_button_action(std::string name,void(*)(std::queue<event*>*));
    void call_item(std::string name,std::queue<event*>* event_queue,item*);
    void call_button(std::string name,std::queue<event*>* event_queue);
};


#endif //OOP_ACTION_HANDLER_H