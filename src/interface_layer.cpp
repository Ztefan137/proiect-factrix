//
// Created by stefa on 5/13/2026.
//

#include "../include/interface_layer.h"

interface_layer::interface_layer(game_session& session) : session(session), g_engine(session.expose<chunk_loader&>("loader"),session.expose<build_system&>("build_system"),window){

}

void interface_layer::process_input() {
    this->handler.process_events(window,g_engine,session);
    this->handler.process_tick_events(window,g_engine,session.expose<build_system&>("build_system"),session.expose<chunk_loader&>("loader"),session.expose<player&>("player"),session.expose<machine_handler&>("machine_handler"));
}

void interface_layer::process_output(){
    this->g_engine.render();
}

bool interface_layer::is_open() {
    return this->window.isOpen();
}

void interface_layer::init() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;
    this->window.create(sf::VideoMode({screenWidth, screenHeight}), "Factrix", sf::State::Fullscreen);
    this->window.setVerticalSyncEnabled(true);

    this->g_engine.load_texture(0,"../assets/configuration files/texture_config.txt");
    this->g_engine.init_camera();
}
