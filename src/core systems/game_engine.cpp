//
// Created by stefa on 3/18/2026.
//

#include "../../include/game_engine.h"

#include "entity_data.h"

/*void game_engine::init(){
    this->init_entity_data();
    this->g_engine.load_texture(0,"../assets/configuration files/texture_config.txt");
    this->init_window();
    this->g_engine.init_camera();
    //this->g_engine.get_camera_system().load textures

    //generic_event<ui_idx_info> curr_event({2});
    //this->internal_ui_system.process_event(&curr_event,&this->event_queue);

    //this->g_engine.get_camera_system().init_camera();
}*/

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
    this->interface.process_input();
    this->session.update();
}

void game_engine::init() {
    entity_data::init();
    this->interface.init();
}

void game_engine::run(){
    while(this->interface.is_open()){
        this->compute_dt();
        this->check_tick();
        this->interface.process_output();
    }
}