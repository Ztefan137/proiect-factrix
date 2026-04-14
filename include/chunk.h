//
// Created by stefa on 3/13/2026.
//

#ifndef OOP_CHUNK_H
#define OOP_CHUNK_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <vector>

#include "world_generator.h"
#include <unordered_map>
#include <string>

class chunk {
    int i;
    int j;
    int ground[32*32];
    int decoratives[32*32];
    bool visible=false;
    float tile_size=64.f;
    std::unordered_map<std::string,sf::VertexArray> grid_layers;
    std::vector<std::string> layers;
    std::vector<sf::Vertex> non_grid_entities;
public:
    chunk()=default;
    chunk(int i,int j,world_generator& generator,float tile_size,bool visibility);
    void compute_va();
    void render(sf::RenderWindow& window_obj,float x,float y,sf::Texture& texture);
    bool is_visible();
    void recompute_top_layer();
};


#endif //OOP_CHUNK_H