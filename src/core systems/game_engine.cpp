//
// Created by stefa on 3/18/2026.
//

#include "../../include/game_engine.h"
#include "entity_data.h"

game_engine::game_engine() : interface(session){

}

void game_engine::compute_dt() {
    this->dt=this->clock.restart().asSeconds();
}

void game_engine::check_tick() {
    static float accumulator = 0.0f;
    const float target_tps=100.f;
    const float tick_interval = 1.0f / target_tps;

    accumulator+=dt;

    while (accumulator >= tick_interval) {
        this->tick();
        accumulator -= tick_interval;
    }
}

void game_engine::tick() {
    this->interface.process_input("tick");
    this->session.update();
}

void game_engine::init() {
    entity_data::init();
    this->interface.init();
}

void game_engine::run(){
    while(this->interface.is_open()){
        this->interface.process_input("frame");
        this->compute_dt();
        this->check_tick();
        this->interface.process_output();
    }
}