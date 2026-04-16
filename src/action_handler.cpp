//
// Created by stefa on 4/16/2026.
//

#include "../include/action_handler.h"

#include <iostream>
#include <ostream>

void action_handler::call_item(std::string name,std::queue<event*>* event_queue,std::string item) {
    this->item_actions[name](event_queue,item);
}

void action_handler::call_button(std::string name,std::queue<event*>* event_queue) {
    this->button_actions[name](event_queue);
}

void action_handler::add_item_action(std::string name, void(*action)(std::queue<event*>* event_queue,std::string)) {
    this->item_actions[name]=action;
}

void action_handler::add_button_action(std::string name, void(*action)(std::queue<event*>* event_queue)) {
    this->button_actions[name]=action;
}
