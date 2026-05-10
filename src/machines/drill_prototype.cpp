//
// Created by stefa on 5/4/2026.
//

#include "../../include/drill_prototype.h"

drill_prototype::drill_prototype(const std::string& mined_tile) : fuel_slot("",0), destination_slot("",0), mined(mined_tile) {
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
