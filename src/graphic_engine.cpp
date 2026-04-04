//
// Created by stefa on 3/16/2026.
//

#include "../include/graphic_engine.h"
#include <cmath>
#include "structures.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "graphic_functions.h"

void graphic_engine::set_camera(float new_x_camera,float new_y_camera) {
    this->x_camera = new_x_camera;
    this->y_camera = new_y_camera;
}
void graphic_engine::set_zoom(float new_zoom_level) {
    this->zoom_level = new_zoom_level;
}

void graphic_engine::set_tile_size(float new_tile_size) {
    this->tile_size=new_tile_size;
}

graphic_engine::graphic_engine(chunk_loader &loader,sf::RenderWindow &window) : loader(loader), x_camera(0), y_camera(0), zoom_level(1.0f), window(window), texture_maps(1), tile_size(64.f){
    this->internal_ui_system.configure_uis("default");
}

void graphic_engine::get_visible_chunks(std::vector<chunk_position>& visible_chunks) const{
    constexpr float scale_factor = 100.f;
    constexpr float CHUNK_SIZE   = 32.f;

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


void graphic_engine::get_chunk_coords(int chunk_i,int chunk_j,float tile_size,int chunk_size,float &x,float &y) const{

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
    for (unsigned int i=0;i<visible_chunks.size();i++){
        chunk *rendered_chunk=this->loader.get_chunk(visible_chunks[i].i,visible_chunks[i].j);
        if (!rendered_chunk) {
            continue;
        }
        float chunk_x=0;
        float chunk_y=0;
        get_chunk_coords(visible_chunks[i].i,visible_chunks[i].j,this->tile_size,32,chunk_x,chunk_y);
        rendered_chunk->render(window,chunk_x,chunk_y,texture_maps[0]);
    }
}
void graphic_engine::load_texture(int index,std::string const &config_file){
    if (config_file == "default") {
        float tile_size=this->tile_size;
        sf::RenderTexture curr_texture({static_cast<unsigned>(tile_size*9),static_cast<unsigned>(tile_size)});
        curr_texture.clear(sf::Color::Transparent);

        std::cout<<"Atlas made\n";
        sf::RectangleShape water({tile_size, tile_size});
        //redRect.setFillColor(sf::Color(0,150,0,255));
        water.setPosition({0.f, 0.f});
        sf::Texture water_texture;
        if (water_texture.loadFromFile("assets/water.jpg")){}
        water_texture.setSmooth(false);
        water.setTexture(&water_texture);

        // Assume tile_size is already defined (e.g., float tile_size = 32.f;)
        sf::RectangleShape blueRect({tile_size, tile_size});
        blueRect.setPosition({tile_size, 0.f});
        sf::Texture blueRect_texture;
        if (blueRect_texture.loadFromFile("assets/dirt2.png")) {}
        blueRect_texture.setSmooth(false);
        blueRect.setTexture(&blueRect_texture);

        sf::RectangleShape sand({tile_size , tile_size });
        sand.setPosition({tile_size * 2, 0.f});
        sf::Texture sand_texture;
        if (sand_texture.loadFromFile("assets/ground_tiles/sand3.png")) {}
        sand.setTexture(&sand_texture);

        sf::RectangleShape cracked_dirt({tile_size, tile_size});
        cracked_dirt.setPosition({tile_size * 3, 0.f});
        sf::Texture cracked_dirt_texture;
        if (cracked_dirt_texture.loadFromFile("assets/dirt4.png")) {}
        cracked_dirt.setTexture(&cracked_dirt_texture);

        sf::RectangleShape dirt({tile_size, tile_size});
        dirt.setPosition({tile_size * 4, 0.f});
        sf::Texture dirt_texture;
        if (dirt_texture.loadFromFile("assets/dirt5.png")) {}
        dirt.setTexture(&dirt_texture);

        sf::RectangleShape salt({tile_size, tile_size});
        salt.setPosition({tile_size * 5, 0.f});
        sf::Texture salt_texture;
        if (salt_texture.loadFromFile("assets/salt.png")) {}
        salt.setTexture(&salt_texture);

        sf::RectangleShape coal({tile_size, tile_size});
        coal.setPosition({tile_size * 6, 0.f});
        sf::Texture coal_texture;
        if (coal_texture.loadFromFile("assets/coal.png")) {}
        coal.setTexture(&coal_texture);

        sf::RectangleShape copper({tile_size, tile_size});
        copper.setPosition({tile_size * 7, 0.f});
        sf::Texture copper_texture;
        if (copper_texture.loadFromFile("assets/copper.png")) {}
        copper.setTexture(&copper_texture);

        sf::RectangleShape iron({tile_size, tile_size});
        iron.setPosition({tile_size * 8, 0.f});
        sf::Texture iron_texture;
        if (iron_texture.loadFromFile("assets/iron.png")) {}
        iron.setTexture(&iron_texture);

        curr_texture.draw(water);
        curr_texture.draw(blueRect);
        curr_texture.draw(sand);
        curr_texture.draw(cracked_dirt);
        curr_texture.draw(dirt);
        curr_texture.draw(salt);
        curr_texture.draw(coal);
        curr_texture.draw(copper);
        curr_texture.draw(iron);

        curr_texture.display();

        sf::Image atlasImage = curr_texture.getTexture().copyToImage();
        if (!atlasImage.saveToFile("../assets/atlas.png")) {
            std::cout << "Failed to save atlas\n";
        } else {
            std::cout << "Atlas saved successfully\n";
        }

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
    this->internal_ui_system.render_uis(this->window);
}
void graphic_engine::render_mouse_position(){
    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window),window.getView());

    auto tileX = static_cast<float>(static_cast<int>((worldPos.x) / this->tile_size));
    auto tileY = static_cast<float>(static_cast<int>((worldPos.y) / this->tile_size));
    rect(window,tileX*this->tile_size,tileY*this->tile_size,(tileX+1)*this->tile_size,(tileY+1)*this->tile_size,sf::Color::White);
}

