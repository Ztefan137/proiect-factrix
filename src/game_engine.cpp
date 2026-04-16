//
// Created by stefa on 3/18/2026.
//

#include "../include/game_engine.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "event_handler.h"

game_engine::game_engine() : build_system(loader),g_engine(loader,build_system,window), player(0.f,0.f){
}

void game_engine::init_window() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;
    this->window.create(sf::VideoMode({screenWidth, screenHeight}), "My Window", sf::State::Fullscreen);
    this->window.setVerticalSyncEnabled(true);
}

void game_engine::render() {
    this->g_engine.render();
}

void game_engine::print_fps() {
    float fps = 1.f / this->dt;
    //std::cout << "FPS: " << fps << "\n";
    this->g_engine.display_fps(fps);
}

void game_engine::compute_dt() {
    this->dt=this->clock.restart().asSeconds();
}

void game_engine::update(float dt) {
    //std::cout<<"Updating for "<<dt<<" milliseconds\n";
}

void game_engine::process_events(){
    this->handler.process_events(this->window,this->g_engine,this->build_system,this->loader,this->player);
}

void game_engine::init(){
    std::cout<<"Init\n";
    this->g_engine.load_texture(0,"../assets/configuration files/texture_config.txt");
    this->init_window();
    this->g_engine.init_camera();
}
void game_engine::run(){
    std::cout<<"Running\n";
    while(this->window.isOpen()) {
        this->print_fps();
        this->compute_dt();
        this->process_events();
        this->update(dt);
        this->render();
    }
}
