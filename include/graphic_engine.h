//
// Created by stefa on 3/16/2026.
//


#ifndef OOP_GRAPHIC_ENGINE_H
#define OOP_GRAPHIC_ENGINE_H
#include "chunk_loader.h"
#include "structures.h"
#include "SFML/Graphics.hpp"
#include <vector>

#include "ui_system.h"

class graphic_engine {
    chunk_loader& loader;
    float x_camera;
    float y_camera;
    float zoom_level;
    sf::RenderWindow& window;
    std::vector<sf::Texture> texture_maps;
    ui_system ui_system;
public:
    graphic_engine(chunk_loader &loader,sf::RenderWindow &window);
    void draw_chunks();
    void set_camera(float x_camera,float y_camera);
    void set_zoom(float zoom_level);
    void get_visible_chunks(std::vector<chunk_position>& visible_chunks);
    void get_chunk_coords(int chunk_i,int chunk_j,float tile_size,int chunk_size,float &x,float &y);
    void load_texture(int index,std::string const &config_file);
    void render_uis();
};


#endif //OOP_GRAPHIC_ENGINE_H
