//
// Created by stefa on 4/17/2026.
//

#include "../../include/furnace_prototype.h"

#include <iostream>
#include <ostream>

#include "belt_prototype.h"

furnace_prototype::furnace_prototype() : machine(),fuel_slot("",0),source_slot("",0),destination_slot("",0){

}

furnace_prototype::furnace_prototype(const furnace_prototype &other) : machine(other), fuel_slot(other.fuel_slot), source_slot(other.source_slot), destination_slot(other.destination_slot), progress(other.progress), curr_fuel(other.curr_fuel) {

}

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

void furnace_prototype::check_input(machine* input) {
    if (input == nullptr) {
        return;
    }
    if (!dynamic_cast<belt_prototype*>(input)){
        return;
    }
    belt_prototype* belt_instance = dynamic_cast<belt_prototype *>(input);
    if (this->source_slot.get_name() != "") {
        this->source_slot=belt_instance->get_cached();
        return;
    }
    this->source_slot.add_quantity(belt_instance->get_cached().get_quantity());
}

void furnace_prototype::check_output(machine* output) {
    if (output == nullptr) {
        return;
    }
    if (!dynamic_cast<belt_prototype*>(output)){
        return;
    }
    std::cout<<"output2";
    //if (this->source_slot.get_name() != "") {
    //}
    //this->source_slot.add_quantity();
}

std::ostream& operator<<(std::ostream &os, const furnace_prototype &furnace) {
    os << ((furnace.fuel_slot.get_name() == "")? "-" : furnace.fuel_slot.get_name())<< " " << furnace.fuel_slot.get_quantity() << "\n";
    os << ((furnace.source_slot.get_name() == "")? "-" : furnace.source_slot.get_name()) << " " << furnace.source_slot.get_quantity() << "\n";
    os << ((furnace.destination_slot.get_name() == "")? "-" : furnace.destination_slot.get_name()) << " " << furnace.destination_slot.get_quantity() << "\n";
    os << furnace.progress << "\n";
    os << furnace.curr_fuel << "\n";
    return os;
}

std::istream& operator>>(std::istream &is, furnace_prototype &furnace) {
    std::string fuel_name;
    int fuel_quantity;
    std::string source_name;
    int source_quantity;
    std::string destination_name;
    int destination_quantity;
    float progress;
    float curr_fuel;

    is >> fuel_name >> fuel_quantity;
    is >> source_name >> source_quantity;
    is >> destination_name >> destination_quantity;
    is >> progress;
    is >> curr_fuel;

    fuel_name=(fuel_name == "-")?"":fuel_name;
    source_name=(source_name == "-")?"":source_name;
    destination_name=(destination_name == "-")?"":destination_name;

    furnace.fuel_slot.set_name(fuel_name);
    furnace.fuel_slot.add_quantity(fuel_quantity);
    furnace.source_slot.set_name(source_name);
    furnace.source_slot.add_quantity(source_quantity);
    furnace.destination_slot.set_name(destination_name);
    furnace.destination_slot.add_quantity(destination_quantity);
    furnace.progress = progress;
    furnace.curr_fuel = curr_fuel;

    return is;
}