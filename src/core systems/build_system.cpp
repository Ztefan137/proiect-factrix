//
// Created by stefa on 4/16/2026.
//

#include "build_system.h"

#include <iostream>

#include "collision_handler.h"
#include "entity_data.h"
#include "furnace_prototype.h"

build_system::build_system(chunk_loader &loader,machine_handler &machine_handler,player &player) : loader(loader),machines(machine_handler) , player_instance(player){

}

std::string build_system::get_item() {
    return this->item;
}

bool build_system::get_on() {
    return this->on;
}

void build_system::set_item(std::string item) {
    this->item = item;
}

void build_system::set_on(bool on) {
    this->on = on;
}

bool build_system::can_build() {
    collision_handler handler(this->loader);
    entity_data data;
    bool collision_found=false;
    for (int i=0;i<data.get_by_name(this->item).width;i++) {
        for (int j=0;j<data.get_by_name(this->item).height;j++) {
            if (handler.is_collision(this->mouse_tile_x-i,this->mouse_tile_y-j)) {
                collision_found=true;
            }
        }
    }
    if (!player_instance.has_item(this->item)) {
        return false;
    }
    return !collision_found;
}

void build_system::set_mouse_tiles(int x, int y) {
    this->mouse_tile_x=x;
    this->mouse_tile_y=y;
}

void build_system::build(){
    if (this->can_build()){
        entity_data data;
        this->loader.add_building(data.get_by_name(this->item).id,this->mouse_tile_x,this->mouse_tile_y);
        this->machines.add_machine(new furnace_prototype(),this->mouse_tile_x,this->mouse_tile_y);
        player_instance.remove_item(this->item,1);
    }
}
