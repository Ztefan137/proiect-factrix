//
// Created by stefa on 3/16/2026.
//

#include "../include/graphic_engine.h"
#include <cmath>
#include "structures.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "graphic_functions.h"
#include "string_functions.h"
#include <deque>

void graphic_engine::init_camera() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;

    sf::Vector2u windowSize = window.getSize();
    float aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    float worldHeight = 1000.f;
    float worldWidth  = worldHeight * aspectRatio;
    this->camera=sf::View(sf::FloatRect({0.f, 0.f}, {worldWidth, worldHeight}));

    constexpr bool high_resolution=true;

    const float ui_width  = high_resolution?2880.f:1920.f;
    const float ui_height = high_resolution?1800.f:1080.f;

    this->ui_camera=sf::View(sf::FloatRect({0.f, 0.f}, {ui_width, ui_height}));
    this->ui_camera.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));
    this->ui_camera.setCenter({screenWidth / 2.f, screenHeight / 2.f});

    this->window.setView(camera);
    this->set_camera(x_camera,y_camera);
    this->set_zoom(zoom_level);
}

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
    //this->internal_ui_system.configure_uis("default");
    this->internal_ui_system.configure_uis("../assets/configuration files/ui.xml");
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
    float tile_size=this->tile_size;
    sf::RenderTexture atlas({static_cast<unsigned>(tile_size*9),static_cast<unsigned>(tile_size)});
    atlas.clear(sf::Color::Transparent);

    std::ifstream config(config_file);
    std::string text_line;
    std::vector<sf::RectangleShape> loaded_rects;
    std::deque<sf::Texture> loaded_textures;
    int processing_step=-1;
    while (std::getline (config, text_line)) {
        auto words = st::split(text_line, ':');
        if (words.size() < 2) continue;
        if (st::trim(words[0]) == "size") {
            if (atlas.resize({static_cast<unsigned>(tile_size*std::stof(st::trim(words[1]))),static_cast<unsigned>(tile_size)})){}
            loaded_rects.reserve(std::stoi(st::trim(words[1])));
        }
        if (st::trim(words[0]) == "texture") {
            processing_step=0;
            loaded_rects.emplace_back();
            loaded_rects.back().setSize({tile_size,tile_size});
        }
        else if (processing_step==0 && st::trim(words[0]) == "position") {
            float position=std::stof(st::trim(words[1]));
            loaded_rects.back().setPosition({tile_size*position,0.f});
            processing_step=1;
        }
        else if (processing_step==1 && st::trim(words[0]) == "path") {
            loaded_textures.emplace_back();
            if (!loaded_textures.back().loadFromFile(st::trim(words[1]))) {
                std::cout << "Failed to load texture\n";
            }
            loaded_rects.back().setTexture(&loaded_textures.back());
            atlas.draw(loaded_rects.back());
            processing_step=-1;
        }else {
            processing_step=-1;
        }
    }
    config.close();
    atlas.display();
    sf::Image atlasImage = atlas.getTexture().copyToImage();
    if (!atlasImage.saveToFile("../assets/atlas.png")) {}

    this->texture_maps.resize(1000);
    this->texture_maps[index]=(sf::Texture(atlas.getTexture()));
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

void graphic_engine::render() {
    this->window.clear(sf::Color::White);
    this->window.setView(camera);
    this->draw_chunks();
    this->render_mouse_position();
    this->window.setView(ui_camera);
    this->render_uis();
    this->window.setView(camera);
    this->window.display();
}

void graphic_engine::zoom(float delta) {
    float zoomFactor = delta > 0 ? 0.9f : 1.1f;
    float newZoom = this->zoom_level * zoomFactor;
    constexpr float min_zoom = 0.7f;
    constexpr float max_zoom = 20.f;
    if (newZoom < min_zoom || newZoom > max_zoom)
        return;

    this->zoom_level = newZoom;
    this->camera.zoom(zoomFactor);
}

void graphic_engine::process_event(std::string event) {
    if (event == "e") {
        this->internal_ui_system.process_event("e");
    }
}
