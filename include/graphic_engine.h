//
// Created by stefa on 3/16/2026.
//


#ifndef OOP_GRAPHIC_ENGINE_H
#define OOP_GRAPHIC_ENGINE_H
#include "chunk_loader.h"
#include "structures.h"
#include "SFML/Graphics.hpp"
#include <vector>

#include "build_system.h"
#include "ui_system.h"
#include "event.h"

#include "queue"

class event_handler;

class graphic_engine {
    chunk_loader& loader;
    build_system& builder;
    sf::View camera;
    sf::View ui_camera;
    float x_camera;
    float y_camera;
    float zoom_level;
    sf::RenderWindow& window;
    std::vector<sf::Texture> texture_maps;
    ui_system internal_ui_system;
    float tile_size;

    bool home_menu=true;

    std::queue <event*> event_queue;
public:
    graphic_engine(chunk_loader &loader,build_system& builder,sf::RenderWindow &window);
    void init_camera();
    void draw_chunks();
    void set_camera(float x_camera,float y_camera);
    void set_zoom(float zoom_level);
    void zoom(float delta);
    void set_tile_size(float new_tile_size);
    void get_visible_chunks(std::vector<chunk_position>& visible_chunks) const;
    void get_chunk_coords(int chunk_i,int chunk_j,float tile_size,int chunk_size,float &x,float &y) const ;
    void load_texture(int index,std::string const &config_file);
    void render_uis();
    void render_mouse_position();
    void display_fps(float fps);
    void render();
    void process_event(event* event);
    void render_player();
    void render_build_mode();
    void render_game();
    void render_home_menu();
    void start_game_rendering();
    void stop_game_rendering();
    int game_rendering_state();
    ui_system& get_ui_system();
    event* get_event();
    sf::Vector2f get_mouse_coords();
    float get_tile_size();
};


#endif //OOP_GRAPHIC_ENGINE_H
