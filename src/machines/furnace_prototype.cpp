//
// Created by stefa on 4/17/2026.
//

#include "../../include/furnace_prototype.h"

#include <iostream>
#include <ostream>

furnace_prototype::furnace_prototype() : machine(),fuel_slot("",0),source_slot("",0),destination_slot("",0){

}

/*void furnace_prototype::update() {
    //logica de update
    if (fuel_slot.get_name() == "coal_ore" && fuel_slot.get_quantity() > 0) {
        if (source_slot.get_name() == "iron_ore" && source_slot.get_quantity() > 0) {
            source_slot.take_quantity(1);
            destination_slot.set_name("iron_plate");
            destination_slot.add_quantity(1);
        }
    }
}*/

void furnace_prototype::update() {
    bool smelting_conditions=false;
    smelting_conditions=source_slot.get_quantity()>0 && this->curr_fuel>0.f;
    if (smelting_conditions && this->progress == 0.f){
        source_slot.take_quantity(1);
        this->progress += 0.01f;
        this->curr_fuel-=0.005f;
    }else if (this->progress > 0.f && this->curr_fuel>0.f){
        this->progress += 0.01f;
        this->curr_fuel-=0.005f;
    }else if (this->progress >0.f && this->curr_fuel<=0.f) {
        //this->progress = 0.f;
    }
    if(this->progress >= 1.f){
        this->progress = 0.f;
        destination_slot.set_name("iron_plate");
        destination_slot.add_quantity(1);
    }
    convert_fuel();
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

float *furnace_prototype::get_progress() {
    return &this->progress;
}

float *furnace_prototype::get_curr_fuel() {
    return &this->curr_fuel;
}
void furnace_prototype::add_fuel(item &item) {
    this->fuel_slot.add_quantity(item.get_quantity());
}

void furnace_prototype::add_source(item &item) {
    this->source_slot=item;
}

void furnace_prototype::convert_fuel(){
    if (this->fuel_slot.get_quantity() > 0 && this->curr_fuel <= 0.f){
        this->fuel_slot.take_quantity(1);
        this->curr_fuel=1.f;
    }
}

