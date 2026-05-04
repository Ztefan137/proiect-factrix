//
// Created by stefa on 3/18/2026.
//

#include "../../include/game_engine.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "entity_data.h"
#include "event_handler.h"

game_engine::game_engine() : build_system(loader,machine_handler,player),g_engine(loader,build_system,window), player(0.f,0.f), machine_handler(player){
}

game_engine::~game_engine() {
    this->machine_handler.delete_machines();
}

void game_engine::init_window() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;
    this->window.create(sf::VideoMode({screenWidth, screenHeight}), "My Window", sf::State::Fullscreen);
    this->window.setVerticalSyncEnabled(true);
}

void game_engine::init_entity_data(){
    entity_data::init();
}

void game_engine::render() {
    this->g_engine.render();
}

void game_engine::compute_dt() {
    this->dt=this->clock.restart().asSeconds();
}

void game_engine::update(float dt) {
    static float accumulator = 0.0f;
    const float target_tps=100.f;
    const float tick_interval = 1.0f / target_tps;

    accumulator += dt;

    while (accumulator >= tick_interval) {
        this->tick();
        accumulator -= tick_interval;
    }
}

void game_engine::tick() {
    this->machine_handler.update_machines();
    this->handler.process_tick_events(this->window,this->g_engine,this->build_system,this->loader,this->player,this->machine_handler);
    this->player.update();
}

void game_engine::process_events(){
    this->handler.process_events(this->window,this->g_engine,this->build_system,this->loader,this->player,this->machine_handler);
}

void game_engine::init(){
    this->init_entity_data();
    this->g_engine.load_texture(0,"../assets/configuration files/texture_config.txt");
    this->init_window();
    this->g_engine.init_camera();
    //this->g_engine.get_camera_system().load textures

    //generic_event<ui_idx_info> curr_event({2});
    //this->internal_ui_system.process_event(&curr_event,&this->event_queue);

    //this->g_engine.get_camera_system().init_camera();
}
void game_engine::run(){
    while(this->window.isOpen()) {
        //astea se executa per frame
        this->compute_dt();
        this->process_events();
        this->update(dt); //asta se amortizeaza la o executie per tick
        this->render();
    }
}
