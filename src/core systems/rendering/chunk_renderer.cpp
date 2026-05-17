//
// Created by stefa on 4/27/2026.
//
#include <cmath>
#include <vector>

#include "chunk_renderer.h"

chunk_renderer::chunk_renderer(chunk_loader &loader, sf::RenderWindow &window, camera_system& camera) : window(window), loader(loader), camera(camera){

}

void chunk_renderer::get_visible_chunks(std::vector<chunk_position>& visible_chunks) const{
    constexpr float scale_factor = 100.f;
    constexpr float CHUNK_SIZE   = 32.f;
    const float zoom_level=camera.get_zoom();
    const float x_camera=camera.get_camera_x();
    const float y_camera=camera.get_camera_y();

    visible_chunks.clear();

    float view_width_world  = std::max(scale_factor * zoom_level,  CHUNK_SIZE);
    float view_height_world = std::max(scale_factor * zoom_level,  CHUNK_SIZE);

    float halfW = view_width_world  * 0.5f;
    float halfH = view_height_world * 0.5f;

    float left   = x_camera - halfW;
    float right  = x_camera + halfW;
    float top    = y_camera - halfH;
    float bottom = y_camera + halfH;

    int chunk_left   = static_cast<int>(std::floor(left   / CHUNK_SIZE));
    int chunk_right  = static_cast<int>(std::floor(right  / CHUNK_SIZE));
    int chunk_top    = static_cast<int>(std::floor(top    / CHUNK_SIZE));
    int chunk_bottom = static_cast<int>(std::floor(bottom / CHUNK_SIZE));

    if (chunk_left > chunk_right) std::swap(chunk_left, chunk_right);
    if (chunk_top > chunk_bottom) std::swap(chunk_top, chunk_bottom);

    for (int ci = chunk_top; ci <= chunk_bottom; ci++) {
        for (int cj = chunk_left; cj <= chunk_right; cj++) {
            visible_chunks.push_back({ci, cj});
        }
    }
}

void chunk_renderer::get_chunk_coords(int chunk_i,int chunk_j,float tile_size,int chunk_size,float &x,float &y) const{

    //const float zoom_level=camera.get_zoom();
    const float x_camera=camera.get_camera_x();
    const float y_camera=camera.get_camera_y();

    const int tile_col_count = static_cast<int>(window.getSize().x / tile_size);
    const int tile_row_count = static_cast<int>(window.getSize().y / tile_size);

    const int center_x = tile_col_count / 2;
    const int center_y = tile_row_count / 2;

    const int camera_chunk_j = static_cast<int>(std::floor(x_camera / chunk_size));
    const int camera_chunk_i = static_cast<int>(std::floor(y_camera / chunk_size));

    float local_x = std::fmod(x_camera, static_cast<float>(chunk_size));
    float local_y = std::fmod(y_camera, static_cast<float>(chunk_size));

    if (local_x < 0) local_x += chunk_size;
    if (local_y < 0) local_y += chunk_size;

    const int delta_x = chunk_j - camera_chunk_j;
    const int delta_y = chunk_i - camera_chunk_i;

    const float chunk_pixel_size = tile_size * chunk_size;

    x = (center_x - local_x) * tile_size + delta_x * chunk_pixel_size;
    y = (center_y - local_y) * tile_size + delta_y * chunk_pixel_size;
}
void chunk_renderer::draw_chunks() {
    std::vector<chunk_position> visible_chunks;
    float chunk_x=0;
    float chunk_y=0;
    this->get_visible_chunks(visible_chunks);
    for (unsigned int i=0;i<visible_chunks.size();i++){
        chunk *rendered_chunk=this->loader.get_chunk(visible_chunks[i].i,visible_chunks[i].j);
        if (rendered_chunk) {
            get_chunk_coords(visible_chunks[i].i,visible_chunks[i].j,this->tile_size,32,chunk_x,chunk_y);
            rendered_chunk->render(window,chunk_x,chunk_y,texture_maps[0]);
        }
    }
}