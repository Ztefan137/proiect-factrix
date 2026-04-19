//
// Created by stefa on 4/16/2026.
//

#ifndef OOP_BUILD_SYSTEM_H
#define OOP_BUILD_SYSTEM_H
#include <string>

#include "chunk_loader.h"
#include "machine.h"
#include "machine_handler.h"

class build_system {
    bool on=false;
    std::string item="";
    chunk_loader &loader;
    int mouse_tile_x=0;
    int mouse_tile_y=0;
    machine_handler &machines;
public:
    build_system(chunk_loader &loader,machine_handler &machine_handler);
    void set_item(std::string item);
    void set_on(bool on);
    std::string get_item();
    bool get_on();
    bool can_build();
    void set_mouse_tiles(int x,int y);
    void build();
};


#endif //OOP_BUILD_SYSTEM_H