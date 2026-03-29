//
// Created by stefa on 3/16/2026.
//

#include "../include/graphic_engine.h"
#include <cmath>
#include "structures.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void graphic_engine::set_camera(float new_x_camera,float new_y_camera) {
    this->x_camera = new_x_camera;
    this->y_camera = new_y_camera;
}
void graphic_engine::set_zoom(float new_zoom_level) {
    this->zoom_level = new_zoom_level;
}

graphic_engine::graphic_engine(chunk_loader &loader,sf::RenderWindow &window) : loader(loader), x_camera(0), y_camera(0), zoom_level(1.0f), window(window), texture_maps(1){
    this->ui_system.configure_uis("default");
}

/*void graphic_engine::get_visible_chunks(std::vector<chunk_position>& visible_chunks) {
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
}*/

void graphic_engine::get_visible_chunks(std::vector<chunk_position>& visible_chunks) {
    const float scale_factor = 100.f;
    const float CHUNK_SIZE   = 32.f;

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

    // Normalize ranges
    if (chunk_left > chunk_right) std::swap(chunk_left, chunk_right);
    if (chunk_top > chunk_bottom) std::swap(chunk_top, chunk_bottom);

    for (int ci = chunk_top; ci <= chunk_bottom; ci++) {
        for (int cj = chunk_left; cj <= chunk_right; cj++) {
            visible_chunks.push_back({ci, cj});
        }
    }
}


void graphic_engine::get_chunk_coords(int chunk_i,int chunk_j,float tile_size,int chunk_size,float &x,float &y){

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
void graphic_engine::draw_chunks() {
    std::vector<chunk_position> visible_chunks;
    this->get_visible_chunks(visible_chunks);
    for (int i=0;i<(int)visible_chunks.size();i++){
        chunk *rendered_chunk=this->loader.get_chunk(visible_chunks[i].i,visible_chunks[i].j);
        if (!rendered_chunk) {
            continue;
        }
        float chunk_x=0;
        float chunk_y=0;
        get_chunk_coords(visible_chunks[i].i,visible_chunks[i].j,32,32,chunk_x,chunk_y);
        rendered_chunk->render(window,chunk_x,chunk_y,texture_maps[0]);
    }
}
void graphic_engine::load_texture(int index,std::string const &config_file){
    if (config_file == "default") {
        sf::RenderTexture curr_texture({32*6,32});
        curr_texture.clear(sf::Color::Transparent);

        std::cout<<"Atlas made\n";

        sf::RectangleShape redRect({100.f, 100.f});
        //redRect.setFillColor(sf::Color(0,150,0,255));
        redRect.setPosition({0.f, 0.f});
        sf::Texture redRect_texture;
        if (redRect_texture.loadFromFile("assets/water.jpg")){}
        redRect.setTexture(&redRect_texture);
        redRect.setSize({32.f,32.f});

        sf::RectangleShape blueRect({100.f, 100.f});
        blueRect.setPosition({32.f, 0.f});
        sf::Texture blueRect_texture;
        if (blueRect_texture.loadFromFile("assets/dirt2.png")){}
        blueRect.setTexture(&blueRect_texture);
        blueRect.setSize({32.f,32.f});

        sf::RectangleShape Rect2({100.f, 100.f});
        Rect2.setFillColor(sf::Color(255, 231, 163,255));
        Rect2.setPosition({32.f*2, 0.f});
        Rect2.setSize({32.f,32.f});

        sf::RectangleShape Rect3({100.f, 100.f});
        Rect3.setFillColor(sf::Color(207, 176, 89,255));
        Rect3.setPosition({32.f*3, 0.f});
        Rect3.setSize({32.f,32.f});

        sf::RectangleShape Rect4({100.f, 100.f});
        Rect4.setFillColor(sf::Color(87, 73, 35,255));
        Rect4.setPosition({32.f*4, 0.f});
        Rect4.setSize({32.f,32.f});

        sf::RectangleShape Rect5({100.f, 100.f});
        Rect5.setFillColor(sf::Color(115, 108, 91,255));
        Rect5.setPosition({32.f*5, 0.f});
        Rect5.setSize({32.f,32.f});

        curr_texture.draw(redRect);
        curr_texture.draw(blueRect);
        curr_texture.draw(Rect2);
        curr_texture.draw(Rect3);
        curr_texture.draw(Rect4);
        curr_texture.draw(Rect5);

        curr_texture.display();

        std::cout<<"Textures loaded\n";
        this->texture_maps.resize(1000);
        this->texture_maps[index]=(sf::Texture(curr_texture.getTexture()));
        //
        //this->texture_maps[index] = copy;
    }
    std::cout << "Vector size: " << this->texture_maps.size() << std::endl;
    std::cout<<"Textures ready\n";
}

void graphic_engine::render_uis() {
    this->ui_system.render_uis(this->window);
}
