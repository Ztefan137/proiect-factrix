//
// Created by stefa on 4/27/2026.
//

#ifndef OOP_CHUNK_RENDERER_H
#define OOP_CHUNK_RENDERER_H
#include "structures.h"
#include <vector>

#include "camera_system.h"
#include "chunk_loader.h"

class chunk_renderer {
    //trebuia sa faca parte dintr un refactor al graphic_engine

    sf::RenderWindow& window;
    std::vector<sf::Texture> texture_maps;
    chunk_loader& loader;
    camera_system& camera;
    float tile_size;
public:
    chunk_renderer(chunk_loader& loader,sf::RenderWindow& window,camera_system &camera_system);
    void draw_chunks();
    void get_visible_chunks(std::vector<chunk_position>& visible_chunks) const;
    void get_chunk_coords(int chunk_i,int chunk_j,float tile_size,int chunk_size,float &x,float &y) const ;
};


#endif //OOP_CHUNK_RENDERER_H