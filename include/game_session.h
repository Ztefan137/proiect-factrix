//
// Created by stefa on 5/12/2026.
//

#ifndef OOP_GAME_SESSION_H
#define OOP_GAME_SESSION_H
#include <iostream>

#include "build_system.h"
#include "chunk_loader.h"
#include "player.h"

class game_session {
    player player;
    chunk_loader loader;
    machine_handler machine_handler;
    build_system build_system;

    //flags
    bool active=false;
    long long int tick_count=0;

public:
    game_session();
    ~game_session();
    friend std::ostream &operator<<(std::ostream &os, const game_session &session);
    void update();
    template<typename T>
    T expose(const std::string& variable) {
        if (variable == "loader") {
            return reinterpret_cast<T>(this->loader);
        }
        if (variable == "build_system") {
            return reinterpret_cast<T>(this->build_system);
        }
        if (variable == "player") {
            return reinterpret_cast<T>(this->player);
        }
        if (variable == "machine_handler") {
            return reinterpret_cast<T>(this->machine_handler);
        }
        throw "interface_binding_error";
    }
    void activate();
    void init(int seed);
    void load(std::string file_path);
    void save(std::string file_path);
    bool is_active() const;
};


#endif //OOP_GAME_SESSION_H