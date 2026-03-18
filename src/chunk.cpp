//
// Created by stefa on 3/13/2026.
//

#include "../include/chunk.h"
#include <SFML/Graphics.hpp>
#include <iostream>

chunk::chunk(int i,int j,world_generator generator,bool visibility){
    this->i=i;
    this->j=j;
    generator.generate_chunk(this->i,this->j,this->ground,this->decoratives);
    this->visible=visibility;
    this->va.setPrimitiveType(sf::PrimitiveType::Triangles);
    this->va.resize(32 * 32 * 6);
}

void chunk::compute_va() {
    const float tile_size = 32.f;
    const int tiles_per_row = 256;

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {

            int tileID = this->ground[i * 32 + j];
            int index = (i * 32 + j) * 6;

            float x0 = j * tile_size;
            float y0 = i * tile_size;
            float x1 = x0 + tile_size;
            float y1 = y0 + tile_size;

            int tu = tileID % tiles_per_row;
            int tv = tileID / tiles_per_row;

            float u0 = tu * tile_size;
            float v0 = tv * tile_size;
            float u1 = u0 + tile_size;
            float v1 = v0 + tile_size;

            this->va[index + 0].position  = {x0, y0};
            this->va[index + 1].position  = {x1, y0};
            this->va[index + 2].position  = {x1, y1};

            this->va[index + 0].texCoords = {u0, v0};
            this->va[index + 1].texCoords = {u1, v0};
            this->va[index + 2].texCoords = {u1, v1};

            this->va[index + 3].position  = {x0, y0};
            this->va[index + 4].position  = {x1, y1};
            this->va[index + 5].position  = {x0, y1};

            this->va[index + 3].texCoords = {u0, v0};
            this->va[index + 4].texCoords = {u1, v1};
            this->va[index + 5].texCoords = {u0, v1};
        }
    }
}

void chunk::render(sf::RenderWindow& window_obj,float x,float y,int tile_size,sf::Texture& texture) {
    sf::RenderStates states;
    states.texture = &texture;
    states.transform.translate({x, y});

    window_obj.draw(this->va,states);

}
bool chunk::is_visible(){
    return this->visible;
}