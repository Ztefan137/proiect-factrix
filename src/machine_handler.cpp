//
// Created by stefa on 4/19/2026.
//

#include "../include/machine_handler.h"

#include <iostream>

#include "furnace_prototype.h"
#include "generic_event.h"
#include "structures.h"

machine_handler::machine_handler(player &player) : player_instance(&player){
}

void machine_handler::add_machine(machine* machine, int x, int y) {
    machines[std::to_string(x)+","+std::to_string(y)]=machine;
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

machine *machine_handler::get_machine(int x, int y) {
    return this->machines[std::to_string(x)+","+std::to_string(y)];
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
            dynamic_cast<furnace_prototype*>(this->machines[this->opened_machines[0]])->get_source()->set_name(item->get_name());
            dynamic_cast<furnace_prototype*>(this->machines[this->opened_machines[0]])->get_source()->add_quantity(item->get_quantity());
            item->take_quantity(item->get_quantity()+1);
        }else if(ge->get_event_data().to == "inventory"){

        }
    }
}

void machine_handler::update_machines() {
    for (auto& [pos, ptr] : machines) {
        ptr->update();
    }
}
