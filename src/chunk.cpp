//
// Created by stefa on 3/13/2026.
//

#include "../include/chunk.h"
#include <SFML/Graphics.hpp>

chunk::chunk(int i,int j,world_generator& generator,float tile_size,bool visibility){
    layers.push_back("ground");
    layers.push_back("decoratives");
    this->i=i;
    this->j=j;
    generator.generate_chunk(this->i,this->j,this->ground,this->decoratives);
    this->tile_size=tile_size;
    this->visible=visibility;
    sf::VertexArray ground_va;
    ground_va.setPrimitiveType(sf::PrimitiveType::Triangles);
    ground_va.resize(32 * 32 * 6);
    this->grid_layers[this->layers[0]] = ground_va;
    sf::VertexArray decoratives_va;
    decoratives_va.setPrimitiveType(sf::PrimitiveType::Triangles);
    decoratives_va.resize(32 * 32 * 6);
    this->grid_layers[this->layers[1]] = decoratives_va;
}

void chunk::compute_va() {
    auto& va_vec = this->non_grid_entities; // A std::vector<sf::Vertex>
    va_vec.clear();
    for (const auto& layer : this->layers) {
        auto& va = this->grid_layers[layer];
        const float tile_size = this->tile_size;
        const int tiles_per_row = 256;

        for (int tile_i = 0; tile_i < 32; tile_i++) {
            for (int tile_j = 0; tile_j < 32; tile_j++) {

                int tileID;
                if (layer == "ground") {
                    tileID = this->ground[tile_i * 32 + tile_j];
                }else{
                    tileID = this->decoratives[tile_i * 32 + tile_j];
                }
                int index = (tile_i * 32 + tile_j) * 6;

                float width_multiplier=1;
                float height_multiplier=1;
                if (tileID == 9) {
                    height_multiplier=3;
                    width_multiplier=2;
                }
                if (tileID == 10) {
                    height_multiplier=2;
                    width_multiplier=2;
                }
                float x1 = (tile_j + 1) * tile_size;
                float y1 = (tile_i + 1) * tile_size;
                float x0 = x1 - (tile_size * width_multiplier);
                float y0 = y1 - (tile_size * height_multiplier);

                int tu = tileID % tiles_per_row;
                int tv = tileID / tiles_per_row;

                float u0 = tu * tile_size;
                float v0 = tv * tile_size;
                float u1 = (tu + 1) * tile_size;
                float v1 = (tv + 1) * tile_size;

                if (tileID == 9 || tileID == 10) {
                    va_vec.push_back(sf::Vertex{.position = {x0, y0}, .texCoords = {u0, v0}});
                    va_vec.push_back(sf::Vertex{.position = {x1, y0}, .texCoords = {u1, v0}});
                    va_vec.push_back(sf::Vertex{.position = {x1, y1}, .texCoords = {u1, v1}});

                    va_vec.push_back(sf::Vertex{.position = {x0, y0}, .texCoords = {u0, v0}});
                    va_vec.push_back(sf::Vertex{.position = {x1, y1}, .texCoords = {u1, v1}});
                    va_vec.push_back(sf::Vertex{.position = {x0, y1}, .texCoords = {u0, v1}});
                }else {
                    va[index + 0].position  = {x0, y0};
                    va[index + 1].position  = {x1, y0};
                    va[index + 2].position  = {x1, y1};

                    va[index + 0].texCoords = {u0, v0};
                    va[index + 1].texCoords = {u1, v0};
                    va[index + 2].texCoords = {u1, v1};

                    va[index + 3].position  = {x0, y0};
                    va[index + 4].position  = {x1, y1};
                    va[index + 5].position  = {x0, y1};

                    va[index + 3].texCoords = {u0, v0};
                    va[index + 4].texCoords = {u1, v1};
                    va[index + 5].texCoords = {u0, v1};
                }
            }
        }
    }
}
void chunk::render(sf::RenderWindow& window_obj,float x,float y,sf::Texture& texture) {
    sf::RenderStates states;
    states.texture = &texture;
    states.transform.translate({x, y});
    for (const auto& layer : this->layers){
        window_obj.draw(this->grid_layers[layer],states);
    }
    auto& va_vec = this->non_grid_entities;
    if (!va_vec.empty()) {
        window_obj.draw(&va_vec[0], va_vec.size(), sf::PrimitiveType::Triangles, states);
    }
}
bool chunk::is_visible(){
    return this->visible;
}