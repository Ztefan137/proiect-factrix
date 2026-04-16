//
// Created by stefa on 3/18/2026.
//
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <graphic_engine.h>
#include <chrono>
#include "player.h"
#include "event_handler.h"

#ifndef OOP_GAME_ENGINE_H
#define OOP_GAME_ENGINE_H

class game_engine {
    sf::RenderWindow window;
    chunk_loader loader;
    graphic_engine g_engine;
    event_handler handler;

    player player;
    //std::vector<machine*> machines;

    sf::Clock clock;
    float dt=0.f;

    std::unordered_map<std::string,bool> key_input;

    void init_window();

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