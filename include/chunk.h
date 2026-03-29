//
// Created by stefa on 3/13/2026.
//

#ifndef OOP_CHUNK_H
#define OOP_CHUNK_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <vector>

#include "world_generator.h"

class chunk {
    int i;
    int j;
    int ground[32*32];
    int decoratives[32*32];
    bool visible=false;
    sf::VertexArray va;
public:
    chunk()=default;
    chunk(int i,int j,world_generator generator,bool visibility);
    void compute_va();
    void render(sf::RenderWindow& window_obj,float x,float y,sf::Texture& texture);
    bool is_visible();
};


#endif //OOP_CHUNK_H