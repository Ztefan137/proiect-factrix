//
// Created by stefa on 4/16/2026.
//

#ifndef OOP_COLLISION_HANDLER_H
#define OOP_COLLISION_HANDLER_H
#include "chunk_loader.h"


class collision_handler {
    chunk_loader& loader;
public:
    collision_handler(chunk_loader &loader);
    bool is_collision(int x,int y);
};


#endif //OOP_COLLISION_HANDLER_H