//
// Created by stefa on 5/4/2026.
//

#ifndef OOP_DRILL_PROTOTYPE_H
#define OOP_DRILL_PROTOTYPE_H
#include "item.h"
#include "machine.h"
#include <string>

#include "belt_prototype.h"


class drill_prototype : public machine{
    item fuel_slot;
    item destination_slot;
    float progress=0.f;
    float curr_fuel=0.f;
    const std::string mined;
    void convert_fuel();
public:
    explicit drill_prototype(const std::string& mined_tile);
    void update() override;
    item* get_fuel();
    item* get_destination();
    float* get_progress();
    float* get_curr_fuel();
    void check_input(machine*) override;
    void check_output(machine*) override;
};


#endif //OOP_DRILL_PROTOTYPE_H