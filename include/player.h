//
// Created by stefa on 4/12/2026.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <vector>
#include "item.h"
#include "deque"
#include "chunk_loader.h"
#include "crafter.h"

class player {
    float x=0;
    float y=0;
    std::vector<item> inventory;
    std::vector<item> crafting_grid;
    float mining_progress=0.f;
    crafter internal_crafter;
public:
    player(float x,float y);
    void move(float dx,float dy,chunk_loader& loader);
    float get_x();
    float get_y();
    item* get_inventory();
    item* get_crafting_grid();
    void add_item(std::string type,int count);
    void remove_item(std::string type,int count);
    bool has_item(std::string type);
    void mine(float dp);
    bool has_mined();
    void update();
    void craft(item item);
};


#endif //OOP_PLAYER_H