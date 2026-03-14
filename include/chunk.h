//
// Created by stefa on 3/13/2026.
//

#ifndef OOP_CHUNK_H
#define OOP_CHUNK_H
#include <SFML/Graphics.hpp>
#include <vector>

#include "world_generator.h"

class chunk{
    int i;
    int j;
    int ground[32*32];
    int decoratives[32*32];
public:
    chunk(int i,int j,world_generator generator);
    void render(sf::RenderWindow& window_obj,float x,float y,int tile_size,std::vector<sf::Sprite> sprites);
};


#endif //OOP_CHUNK_H