//
// Created by stefa on 4/19/2026.
//

#include "../include/machine_handler.h"

#include <iostream>

#include "belt_prototype.h"
#include "drill_prototype.h"
#include "furnace_prototype.h"
#include "generic_event.h"
#include "string_functions.h"
#include "structures.h"

machine_handler::machine_handler(player &player) : player_instance(&player){
}

void machine_handler::add_machine(machine* machine, int x, int y) {
    if (dynamic_cast<belt_prototype*>(machine)) {
        belts[std::to_string(x)+","+std::to_string(y)]=dynamic_cast<belt_prototype*>(machine);
    }else {
        machines[std::to_string(x)+","+std::to_string(y)]=machine;
    }
}

void machine_handler::delete_machine(int x, int y) {
    delete machines[std::to_string(x)+","+std::to_string(y)];
}

void machine_handler::delete_machines() {
    for (auto& [pos, ptr] : machines) {
        delete ptr;
    }
    machines.clear();
}

machine* machine_handler::get_machine(int x, int y) {
    if (machines.contains(std::to_string(x)+","+std::to_string(y))) {
        return machines[std::to_string(x)+","+std::to_string(y)];
    }else {
        return nullptr;
    }
}

belt_prototype* machine_handler::get_belt(int x, int y) {
    if (belts.contains(std::to_string(x)+","+std::to_string(y))) {
        return belts[std::to_string(x)+","+std::to_string(y)];
    }else{
        return nullptr;
    }
}

void machine_handler::open_machine(int x, int y) {
    this->opened_machines.push_back(std::to_string(x)+","+std::to_string(y));
}

void machine_handler::close_machines() {
    std::cout<<"closing machines"<<std::endl;
    this->opened_machines.clear();
}

void machine_handler::process_event(event *event) {
    if (auto ge=dynamic_cast<generic_event<item_move_data>*>(event)){
        if (ge->get_event_data().to == "furnace"){
            item* item=dynamic_cast<generic_event<item_move_data>*>(event)->get_event_data().source;
            std::cout<<"\nMachine position keys\n";
            for (const auto& pair : machines) {
                std::cout << pair.first << "\n";
            }
            std::cout<<this->opened_machines[0]<<"\n";
            if (item->get_name() == "copper_ore" || item->get_name() == "iron_ore") {
                dynamic_cast<furnace_prototype*>(this->machines[this->opened_machines[0]])->get_source()->set_name(item->get_name());
                dynamic_cast<furnace_prototype*>(this->machines[this->opened_machines[0]])->get_source()->add_quantity(item->get_quantity());
            }else if (item->get_name() == "coal_ore") {
                dynamic_cast<furnace_prototype*>(this->machines[this->opened_machines[0]])->get_fuel()->set_name(item->get_name());
                dynamic_cast<furnace_prototype*>(this->machines[this->opened_machines[0]])->get_fuel()->add_quantity(item->get_quantity());
            }
            item->take_quantity(item->get_quantity());
        }else if(ge->get_event_data().to == "drill"){
            item* item=dynamic_cast<generic_event<item_move_data>*>(event)->get_event_data().source;
            std::cout<<"item added:"<<item->get_quantity()<<"\n";
            std::cout<<"\nMachine position keys\n";
            for (const auto& pair : machines) {
                std::cout << pair.first << "\n";
            }
            std::cout<<this->opened_machines[0]<<"\n";
            if (item->get_name() == "coal_ore") {;
                dynamic_cast<drill_prototype*>(this->machines[this->opened_machines[0]])->get_fuel()->set_name(item->get_name());
                dynamic_cast<drill_prototype*>(this->machines[this->opened_machines[0]])->get_fuel()->add_quantity(item->get_quantity());
            }
            item->take_quantity(item->get_quantity());
        }else if(ge->get_event_data().to == "inventory"){
            ge->get_event_data().source->take_quantity(ge->get_event_data().source->get_quantity());
        }
    }
}

void machine_handler::update_machines() {
    for (auto& [pos,ptr]:belts) {
        ptr->cache_items();
    }
    for (auto& [pos,ptr]:belts) {
        machine* previous=this->get_belt(std::stoi(st::split(pos,',')[0])-1,std::stoi(st::split(pos,',')[1]));
        machine* left=nullptr;
        machine* right=nullptr;
        ptr->move_items(dynamic_cast<belt_prototype *>(previous),dynamic_cast<belt_prototype *>(left),dynamic_cast<belt_prototype *>(right));
    }
    for (auto& [pos, ptr] : machines) {
        machine* previous=this->get_belt(std::stoi(st::split(pos,',')[0]),std::stoi(st::split(pos,',')[1])-2);
        ptr->check_input(previous);
        ptr->update();
        machine* output=this->get_belt(std::stoi(st::split(pos,',')[0]),std::stoi(st::split(pos,',')[1])+1);
        ptr->check_output(output);
    }
}
