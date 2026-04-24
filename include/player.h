//
// Created by stefa on 4/12/2026.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <vector>
#include "item.h"
#include "deque"
#include "chunk_loader.h"

class player {
    float x=0;
    float y=0;
    std::vector<item> inventory;
    float mining_progress=0.f;
public:
    player(float x,float y);
    void move(float dx,float dy,chunk_loader& loader);
    float get_x();
    float get_y();
    item* get_inventory();
    void add_item(std::string type,int count);
    void remove_item(std::string type,int count);
    bool has_item(std::string type);
    void mine(float dp);
    bool has_mined();
};


#endif //OOP_PLAYER_H