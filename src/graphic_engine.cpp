//
// Created by stefa on 3/16/2026.
//

#include "../include/graphic_engine.h"
#include <cmath>
#include "structures.h"
#include <SFML/Graphics.hpp>

void graphic_engine::set_camera(float x_camera,float y_camera) {
    this->x_camera = x_camera;
    this->y_camera = y_camera;
}
void graphic_engine::set_zoom(float zoomLevel) {
    this->zoom_level = zoomLevel;
}


graphic_engine::graphic_engine(chunk_loader &loader,sf::Texture &texture,sf::RenderWindow &window) : loader(loader), x_camera(0), y_camera(0), zoom_level(1.0f), texture(texture), window(window){
}

void graphic_engine::get_visible_chunks(std::vector<chunk_position>& visible_chunks){
    const float scale_factor=100;
    visible_chunks.clear();

    float view_width_world  = scale_factor * zoom_level;
    float view_height_world = scale_factor * zoom_level;

    float halfW = view_width_world  * 0.5f;
    float halfH = view_height_world * 0.5f;

    float left   = x_camera - halfW;
    float right  = x_camera + halfW;
    float top    = y_camera - halfH;
    float bottom = y_camera + halfH;

    const float CHUNK_SIZE = 32.0f;

    int chunk_left   = static_cast<int>(std::floor(left   / CHUNK_SIZE));
    int chunk_right  = static_cast<int>(std::floor(right  / CHUNK_SIZE));
    int chunk_top    = static_cast<int>(std::floor(top    / CHUNK_SIZE));
    int chunk_bottom = static_cast<int>(std::floor(bottom / CHUNK_SIZE));

    for (int ci = chunk_top; ci <= chunk_bottom; ci++) {
        for (int cj = chunk_left; cj <= chunk_right; cj++) {
            visible_chunks.push_back({ci, cj});
        }
    }
}

void graphic_engine::get_chunk_coords(int chunk_i,int chunk_j,float tile_size,int chunk_size,float &x,float &y){

    const int tile_col_count = (int)(window.getSize().x / tile_size);
    const int tile_row_count = (int)(window.getSize().y / tile_size);

    const int center_x = tile_col_count / 2;
    const int center_y = tile_row_count / 2;

    const int camera_chunk_j = (int)(std::floor(x_camera / chunk_size));
    const int camera_chunk_i = (int)(std::floor(y_camera / chunk_size));

    float local_x = std::fmod(x_camera, (float)(chunk_size));
    float local_y = std::fmod(y_camera, (float)(chunk_size));

    if (local_x < 0) local_x += chunk_size;
    if (local_y < 0) local_y += chunk_size;

    const int delta_x = chunk_j - camera_chunk_j;
    const int delta_y = chunk_i - camera_chunk_i;

    const float chunk_pixel_size = tile_size * chunk_size;

    x = (center_x - local_x) * tile_size + delta_x * chunk_pixel_size;
    y = (center_y - local_y) * tile_size + delta_y * chunk_pixel_size;
}
void graphic_engine::draw_chunks() {
    std::vector<chunk_position> visible_chunks;
    this->get_visible_chunks(visible_chunks);
    for (int i=0;i<visible_chunks.size();i++){
        chunk *rendered_chunk=this->loader.get_chunk(visible_chunks[i].i,visible_chunks[i].j);
        float chunk_x=0;
        float chunk_y=0;
        get_chunk_coords(visible_chunks[i].i,visible_chunks[i].j,32,32,chunk_x,chunk_y);
        rendered_chunk->render(window,chunk_x,chunk_y,32,texture);
    }
}