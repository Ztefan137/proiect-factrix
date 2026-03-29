//
// Created by stefa on 3/18/2026.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <string>
#include <graphic_engine.h>

#ifndef OOP_GAME_ENGINE_H
#define OOP_GAME_ENGINE_H

class game_engine {
    //general stuff
    sf::RenderWindow window;
    chunk_loader loader;
    graphic_engine g_engine;
    //logic_engine l_engine;
    //other
    std::unordered_map<std::string,bool> key_input;
public:
    game_engine();
    void init();
    void run();
};


#endif //OOP_GAME_ENGINE_H