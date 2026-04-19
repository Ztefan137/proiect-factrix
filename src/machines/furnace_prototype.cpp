//
// Created by stefa on 4/17/2026.
//

#include "../../include/furnace_prototype.h"

#include <iostream>
#include <ostream>

furnace_prototype::furnace_prototype() : machine(),fuel_slot("coal_ore",10),source_slot("",0),destination_slot("",0){

}

void furnace_prototype::update() {
    //logica de update
    if (fuel_slot.get_name() == "coal_ore" && fuel_slot.get_quantity() > 0) {
        if (source_slot.get_name() == "iron_ore" && source_slot.get_quantity() > 0) {
            source_slot.take_quantity(1);
            destination_slot.set_name("iron_plate");
            destination_slot.add_quantity(1);
        }
    }
}

item* furnace_prototype::get_fuel() {
    return &this->fuel_slot;
}

item* furnace_prototype::get_source() {
    return &this->source_slot;
}

item* furnace_prototype::get_destination() {
    return &this->destination_slot;
}

void furnace_prototype::add_destination(item &item) {

}

void furnace_prototype::add_fuel(item &item) {

}

void furnace_prototype::add_source(item &item) {
    this->source_slot=item;
}
