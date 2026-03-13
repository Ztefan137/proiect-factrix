//
// Created by stefa on 3/13/2026.
//

#include "chunk.h"

chunk::chunk(world_generator generator) {
    generator.generate_chunk(this->i,this->j,this->ground,this->decoratives);
}

void chunk::render(sf::RenderWindow &window_obj, float x, float y, int tile_size, std::vector<sf::Sprite> sprites) {

}
