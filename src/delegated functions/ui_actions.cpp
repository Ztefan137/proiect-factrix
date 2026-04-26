//
// Created by stefa on 4/4/2026.
//
#include "ui_actions.h"
#include "generic_event.h"
#include <iostream>

#include "entity_data.h"

void open_build_mode(std::queue<event*>* event_queue,item* item) {
    std::cout<<"opening build mode with item"<<item<<std::endl;
    build_mode_info info;
    entity_data data;
    info.current_building=data.get_by_name(item->get_name()).id;
    event* test_event=new generic_event<build_mode_info>(info); //NOLINT
    event_queue->push(test_event);
}

void furnace_item_transfer(std::queue<event*>* event_queue,item* item) {
    if (item->get_name() == "iron_ore" || item->get_name() == "copper_ore") {
        item_move_data info;
        info.name=item->get_name();
        info.source=item;
        info.to="furnace";
        event* event=new generic_event<item_move_data>(info); //NOLINT
        event_queue->push(event);
    }
}

void player_item_transfer(std::queue<event *> *event_queue,item* item) {
    item_move_data info;
    info.name=item->get_name();
    info.source=item;
    info.to="inventory";
    event* event=new generic_event<item_move_data>(info); //NOLINT
    event_queue->push(event);
}

void new_game(std::queue<event *> *event_queue) {
    std::cout<<"mouse_clicked"<<std::endl;
    simple_event_data info{1};
    event* event=new generic_event<simple_event_data>(info); //NOLINT
    event_queue->push(event);
}

void continue_game(std::queue<event *> *event_queue) {

}

void load_game(std::queue<event *> *event_queue) {

}

void quit_game(std::queue<event *> *event_queue) {
    
}
void craft_action(std::queue<event *> *event_queue,item* item) {
    event* event=new generic_event<crafting_event_data>({item}); //NOLINT
    event_queue->push(event);
}