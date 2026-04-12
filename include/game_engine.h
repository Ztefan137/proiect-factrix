//
// Created by stefa on 3/18/2026.
//
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <graphic_engine.h>
#include <chrono>

#ifndef OOP_GAME_ENGINE_H
#define OOP_GAME_ENGINE_H

class game_engine {
    sf::RenderWindow window;
    chunk_loader loader;
    graphic_engine g_engine;

    sf::View camera;
    sf::View ui_camera;
    float x_camera = 0.f;
    float y_camera = 0.f;
    float zoomLevel = 1.f;

    sf::Clock clock;
    float dt;

    std::unordered_map<std::string,bool> key_input;

    void init_window();
    void init_cameras();

    void process_events();

    void update(float dt);
    void render();

    void compute_dt();
    void print_fps();

public:
    game_engine();
    void init();
    void run();
};

#endif //OOP_GAME_ENGINE_H