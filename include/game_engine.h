//
// Created by stefa on 3/18/2026.
//
#include <SFML/Graphics.hpp>
#include "game_session.h"
#include "interface_layer.h"

#ifndef OOP_GAME_ENGINE_H
#define OOP_GAME_ENGINE_H

class game_engine {
    game_session session;
    interface_layer interface;

    sf::Clock clock;
    float dt=0.f;

    void compute_dt();
    void check_tick();
    void tick();
public:
    game_engine();
    ~game_engine()=default;
    void init();
    void run();
};

#endif //OOP_GAME_ENGINE_H