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
    public:
    furnace_prototype();
    void update() override;
    item* get_source();
    item* get_destination();
    item* get_fuel();
    void add_source(item &item);
    void add_destination(item &item);
    void add_fuel(item &item);
};


#endif //OOP_FURNACE_PROTOTYPE_H