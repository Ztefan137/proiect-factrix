//
// Created by stefa on 3/13/2026.
//

#include "../include/chunk.h"

chunk::chunk(int i,int j,world_generator generator) {
    this->i=i;
    this->j=j;
    generator.generate_chunk(this->i,this->j,this->ground,this->decoratives);
}

void chunk::render(sf::RenderWindow& window_obj,float x,float y,int tile_size,std::vector<sf::Sprite> sprites) {
    for(int i=0;i<32;i++){
        for(int j=0;j<32;j++){
            sprites[ground[i*32+j]].setPosition({j*150+x, i*150+y});
            window_obj.draw(sprites[ground[i*32+j]]);
        }
    }
}
