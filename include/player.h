//
// Created by stefa on 4/12/2026.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include <vector>
#include "item.h"

class player {
    float x=0;
    float y=0;
    std::vector<item> inventory;
public:
    player(float x,float y);
    void move(float dx,float dy);
    float get_x();
    float get_y();
    item* get_inventory();
};


#endif //OOP_PLAYER_H