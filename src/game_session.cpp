//
// Created by stefa on 5/12/2026.
//

#include "../include/game_session.h"
#include <fstream>

#include "string_functions.h"

game_session::game_session() : player(0,0),machine_handler(player), build_system(loader,machine_handler,player) {

}

game_session::~game_session() {
    this->machine_handler.delete_machines();
}

void game_session::update() {
    if (this->active) {
        this->tick_count++;
        this->machine_handler.update_machines();
        this->player.update();
    }
}

void game_session::activate() {
    this->active=true;
}

void game_session::init(int seed){
    this->activate();
    this->loader.init(seed);
    this->machine_handler.delete_machines();
    this->player.set_position(0,0);
    this->player.clear_inventory();
    this->seed=seed;
}

void game_session::load(std::string file_path) {
    std::ifstream is(file_path);
    std::string tag;

    while (is >> tag) {
        if (tag == "\n") {
            continue;
        }
        if (tag == "[SEED]") {
            is>>this->seed;
            this->init(this->seed);
        } else if (tag == "[PLAYER]") {
            std::cout<<"reading player";
            is >> this->player;
        } else if (tag == "[MACHINES]") {
            std::cout<<"reading machines";
            is >> this->machine_handler;
        } else if (tag == "[CHUNKS]") {
            std::cout<<"reading chunks";
            is >> this->loader;
        }
    }
}

void game_session::save(std::string file_path) {
    std::ofstream file(file_path);
    operator <<(file,*this);
    //file.close();
}

bool game_session::is_active() const{
    return this->active;
}

std::ostream& operator<<(std::ostream& os,const game_session& game_session){
    operator<<(os,"[SEED]\n");
    os<<game_session.seed;
    operator<<(os,"\n");
    operator<<(os,game_session.player);
    operator<<(os,"\n");
    operator<<(os,game_session.machine_handler);
    operator<<(os,"\n");
    operator<<(os,game_session.loader);
    return os;
}
