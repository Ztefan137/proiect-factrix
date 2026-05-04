//
// Created by stefa on 4/17/2026.
//

#ifndef OOP_FURNACE_PROTOTYPE_H
#define OOP_FURNACE_PROTOTYPE_H
#include "item.h"
#include "machine.h"

class furnace_prototype : public machine{
    item fuel_slot;
    item source_slot;
    item destination_slot;
    float progress=0.f;
    float curr_fuel=0.f;
    public:
    furnace_prototype();
    void update() override;
    item* get_source();
    item* get_destination();
    item* get_fuel();
    float* get_progress();
    float* get_curr_fuel();
    void add_source(item &item);
    void add_fuel(item &item);
    void convert_fuel();
};


#endif //OOP_FURNACE_PROTOTYPE_H