//
// Created by stefa on 4/4/2026.
//
#include "ui_actions.h"
#include "generic_event.h"
#include <iostream>

void open_build_mode(std::queue<event*>* event_queue,std::string item) {
    std::cout<<"opening build mode with item"<<item<<std::endl;
    build_mode_info info;
    info.current_building=10;
    event* test_event=new generic_event<build_mode_info>(info); //NOLINT
    event_queue->push(test_event);
}