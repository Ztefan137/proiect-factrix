//
// Created by stefa on 4/16/2026.
//

#include "../include/collision_handler.h"

#include "entity_data.h"

collision_handler::collision_handler(chunk_loader &loader) : loader(loader) {

}

bool collision_handler::is_collision(int x, int y) {
    entity_data data;
    bool ground_collision=false;
    bool decorative_collision=false;
    bool building_collision=false;
    if (data.get_by_id(loader.peak_tile(x,y,"ground")).solid) {
        ground_collision=true;
    }
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (data.get_by_id(loader.peak_tile(x+i,y+j,"decoratives")).solid && data.get_by_id(loader.peak_tile(x+i,y+j,"decoratives")).width>i && data.get_by_id(loader.peak_tile(x+i,y+j,"decoratives")).height>j) {
                decorative_collision=true;
            }
        }
    }

    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if ((data.get_by_id(loader.peak_tile(x+i,y+j,"buildings")).solid && loader.peak_tile(x+i,y+j,"buildings") != 0) && data.get_by_id(loader.peak_tile(x+i,y+j,"buildings")).width>i && data.get_by_id(loader.peak_tile(x+i,y+j,"buildings")).height>j) {
                building_collision=true;
            }
        }
    }

    return ground_collision || building_collision || decorative_collision;
}
