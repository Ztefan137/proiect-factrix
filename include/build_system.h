//
// Created by stefa on 4/16/2026.
//

#ifndef OOP_BUILD_SYSTEM_H
#define OOP_BUILD_SYSTEM_H
#include <string>

#include "chunk_loader.h"

class build_system {
    bool on=false;
    std::string item="";
    chunk_loader &loader;
    int mouse_tile_x;
    int mouse_tile_y;
public:
    build_system(chunk_loader &loader);
    void set_item(std::string item);
    void set_on(bool on);
    std::string get_item();
    bool get_on();
    bool can_build();
    void set_mouse_tiles(int x,int y);
    void build();
};


#endif //OOP_BUILD_SYSTEM_H