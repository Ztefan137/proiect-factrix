//
// Created by stefa on 4/16/2026.
//

#include "collision_handler.h"

collision_handler::collision_handler(chunk_loader &loader) : loader(loader) {

}

bool collision_handler::is_collision(int x, int y) {
    if (loader.peak_tile(x,y) == 0) {
        return true;
    }
    return false;
}
