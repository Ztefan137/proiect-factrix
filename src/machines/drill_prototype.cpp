//
// Created by stefa on 5/4/2026.
//

#include "../../include/drill_prototype.h"

#include <iostream>

#include "belt_prototype.h"

drill_prototype::drill_prototype(const std::string& mined_tile) : machine(), fuel_slot("",0), destination_slot("",0), mined(mined_tile) {
}

void drill_prototype::update() {
    bool drilling_conditions=false;
    drilling_conditions=this->curr_fuel>0.f;
    if (drilling_conditions && this->progress == 0.f){
        //source_slot.take_quantity(1);
        this->progress += 0.01f;
        this->curr_fuel-=0.005f;
    }else if (this->progress > 0.f && this->curr_fuel>0.f){
        this->progress += 0.01f;
        this->curr_fuel-=0.002f;
    }else if (this->progress >0.f && this->curr_fuel<=0.f) {
        //this->progress = 0.f;
    }
    if(this->progress >= 1.f){
        this->progress = 0.f;
        destination_slot.set_name((this->mined == "iron")?"iron_ore":((this->mined == "coal")?"coal_ore":"copper_ore"));
        destination_slot.add_quantity(1);
    }
    convert_fuel();
}

float *drill_prototype::get_progress() {
    return &this->progress;
}

float *drill_prototype::get_curr_fuel() {
    return &this->curr_fuel;
}

item *drill_prototype::get_destination() {
    return &this->destination_slot;
}

item *drill_prototype::get_fuel() {
    return &this->fuel_slot;
}

void drill_prototype::convert_fuel() {
    if (this->fuel_slot.get_quantity() > 0 && this->curr_fuel <= 0.f){
        this->fuel_slot.take_quantity(1);
        this->curr_fuel=1.f;
    }
}

void drill_prototype::check_input(machine* input){

}

void drill_prototype::check_output(machine* output) {
    if (output == nullptr) {
        return;
    }
    if (!dynamic_cast<belt_prototype*>(output)){
        return;
    }
    belt_prototype* belt=dynamic_cast<belt_prototype*>(output);
    std::cout<<this->destination_slot.get_name()<<"\n";
    belt->place_item({this->destination_slot.get_name(),1});
    this->destination_slot.take_quantity(1);
}

std::ostream& operator<<(std::ostream &os, const drill_prototype &drill) {
    os << ((drill.fuel_slot.get_name() == "")? "-" : drill.fuel_slot.get_name())<< " " << drill.fuel_slot.get_quantity() << "\n";
    os << ((drill.destination_slot.get_name() == "")? "-" : drill.destination_slot.get_name())<< " " << drill.destination_slot.get_quantity() << "\n";
    os << drill.progress << "\n";
    os << drill.curr_fuel << "\n";
    os << drill.mined << "\n";
    return os;
}

std::istream& operator>>(std::istream &is, drill_prototype &drill) {
    std::string fuel_name;
    int fuel_quantity;
    std::string destination_name;
    int destination_quantity;
    float progress;
    float curr_fuel;
    std::string mined;

    is >> fuel_name >> fuel_quantity;
    is >> destination_name >> destination_quantity;
    is >> progress;
    is >> curr_fuel;
    is >> mined;

    fuel_name=(fuel_name == "-")?"":fuel_name;
    destination_name=(destination_name == "-")?"":destination_name;

    drill.fuel_slot.set_name(fuel_name);
    drill.fuel_slot.add_quantity(fuel_quantity);
    drill.destination_slot.set_name(destination_name);
    drill.destination_slot.add_quantity(destination_quantity);
    drill.progress = progress;
    drill.curr_fuel = curr_fuel;

    return is;
}