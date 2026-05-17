//
// Created by stefa on 5/12/2026.
//

#include "../include/game_session.h"
#include <fstream>

#include "generic_event.h"
#include "string_functions.h"
#include "structures.h"

game_session::game_session() : player_instance(0,0),machine_handler_instance(player_instance), build_system_instance(loader,machine_handler_instance,player_instance) {

}

game_session::~game_session() {
    this->machine_handler_instance.delete_machines();
}

void game_session::update() {
    if (this->active) {
        this->tick_count++;
        this->machine_handler_instance.update_machines();
        this->player_instance.update();
    }
}

void game_session::activate() {
    this->active=true;
}

void game_session::init(int seed){
    this->activate();
    this->loader.init(seed);
    this->machine_handler_instance.delete_machines();
    this->player_instance.set_position(0,0);
    this->player_instance.clear_inventory();
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
            is >> this->player_instance;
        } else if (tag == "[MACHINES]") {
            std::cout<<"reading machines";
            is >> this->machine_handler_instance;
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
    operator<<(os,game_session.player_instance);
    operator<<(os,"\n");
    operator<<(os,game_session.machine_handler_instance);
    operator<<(os,"\n");
    operator<<(os,game_session.loader);
    return os;
}

void game_session::process_event(event *event) {
    if (auto* pme=dynamic_cast<generic_event<player_move_data>*>(event)) {
        this->player_instance.move(pme->get_event_data().dx,pme->get_event_data().dy,this->loader);
        return;
    }
    if (auto* text_event=dynamic_cast<generic_event<simple_event_text>*>(event)) {
        std::string text=text_event->get_event_data().text;
        if (text == "build_system_off") {
            this->build_system_instance.set_on(false);
            return;
        }
        if (text == "build_system_on") {
            this->build_system_instance.set_on(true);
            return;
        }
        if (text == "close_machines") {
            this->machine_handler_instance.close_machines();
        }
    }
}
