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
        std::cout<<"game_session::update";
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
}

void game_session::load(std::string file_path) {

    std::cout<<"start_load";

    this->init(123);
    std::ifstream file(file_path);
    std::string line;
    std::getline(file,line);
    float x=std::stof(st::split(line,' ')[0]);
    float y=std::stof(st::split(line,' ')[1]);
    this->player.set_position(x,y);

    std::cout<<"end_load";

    //file.close();
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
    operator<<(os,game_session.player);
    return os;
}
