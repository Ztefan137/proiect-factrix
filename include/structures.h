//
// Created by stefa on 3/16/2026.
//

#ifndef OOP_STRUCTURES_H
#define OOP_STRUCTURES_H
#include <string>


struct chunk_position {
    int i,j;
};

struct mouse_position {
    int x,y;
};

struct build_mode_info {
    int current_building=0;
};

struct entity_data_prototype {
    int id;
    std::string name;
    int width,height;
    int graphic_width,graphic_height;
    bool solid=false;
    bool buildable=false;
    std::string texture_path;
};

#endif //OOP_STRUCTURES_H