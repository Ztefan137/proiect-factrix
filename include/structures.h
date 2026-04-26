//
// Created by stefa on 3/16/2026.
//

#ifndef OOP_STRUCTURES_H
#define OOP_STRUCTURES_H
#include <string>

#include "item.h"


struct chunk_position {
    int i,j;
};

struct mouse_position {
    int x,y;
};

struct build_mode_info {
    int current_building=0;
};

struct ui_idx_info {
    int ui_idx=0;
};

struct entity_data_prototype {
    int id;
    std::string name;
    int width,height;
    int graphic_width,graphic_height;
    bool solid=false;
    bool buildable=false;
    std::string texture_path;
    int ui_idx=0;
};

struct item_move_data {
    std::string name;
    //int quantity
    item* source;
    std::string to;
};

struct simple_event_data {
    int event_id;
};

struct mining_info {
    int tile_x=0,tile_y=0;
};

struct crafting_event_data {
    item* crafted;
};

#endif //OOP_STRUCTURES_H