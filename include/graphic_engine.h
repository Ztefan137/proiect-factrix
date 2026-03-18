//
// Created by stefa on 3/16/2026.
//


#ifndef OOP_GRAPHIC_ENGINE_H
#define OOP_GRAPHIC_ENGINE_H
#include "chunk_loader.h"
#include "structures.h"
#include "SFML/Graphics.hpp"

class graphic_engine {
    chunk_loader& loader;
    float x_camera;
    float y_camera;
    float zoom_level;
    sf::Texture& texture;
    sf::RenderWindow& window;
public:
    graphic_engine(chunk_loader &loader,sf::Texture &texture,sf::RenderWindow &window);
    void draw_chunks();
    void set_camera(float x_camera,float y_camera);
    void set_zoom(float zoom_level);
    void get_visible_chunks(std::vector<chunk_position>& visible_chunks);
    void get_chunk_coords(int chunk_i,int chunk_j,float tile_size,int chunk_size,float &x,float &y);

};


#endif //OOP_GRAPHIC_ENGINE_H
