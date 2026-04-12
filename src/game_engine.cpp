//
// Created by stefa on 3/18/2026.
//

#include "../include/game_engine.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

game_engine::game_engine() : g_engine(loader,window){

}

void game_engine::init_window() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;
    this->window.create(sf::VideoMode({screenWidth, screenHeight}), "My Window", sf::State::Fullscreen);
    this->window.setVerticalSyncEnabled(true);
}

void game_engine::init_cameras() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;

    sf::Vector2u windowSize = window.getSize();
    float aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    float worldHeight = 1000.f;
    float worldWidth  = worldHeight * aspectRatio;
    this->camera=sf::View(sf::FloatRect({0.f, 0.f}, {worldWidth, worldHeight}));

    bool high_resolution=true;

    const float ui_width  = high_resolution?2880.f:1920.f;
    const float ui_height = high_resolution?1800.f:1080.f;

    this->ui_camera=sf::View(sf::FloatRect({0.f, 0.f}, {ui_width, ui_height}));
    this->ui_camera.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));
    this->ui_camera.setCenter({screenWidth / 2.f, screenHeight / 2.f});

    this->window.setView(camera);
    this->g_engine.set_camera(x_camera,y_camera);
    this->g_engine.set_zoom(zoomLevel);
}

void game_engine::render() {
    this->window.clear(sf::Color::White);
    this->window.setView(camera);
    this->g_engine.draw_chunks();
    this->g_engine.render_mouse_position();
    this->window.setView(ui_camera);
    this->g_engine.render_uis();
    this->window.setView(camera);
    this->window.display();
}

void game_engine::print_fps() {
    float fps = 1.f / this->dt;
    std::cout << "FPS: " << fps << "\n";
}

void game_engine::compute_dt() {
    this->dt=this->clock.restart().asSeconds();
}

void game_engine::update(float dt) {
    std::cout<<"Updating for "<<dt<<" milliseconds\n";
}

void game_engine::process_events() {
    bool shouldExit = false;
    while(const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            std::cout << "Fereastra a fost închisă\n";
        }
        else if (event->is<sf::Event::KeyPressed>()) {
            const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
            std::cout << "Received key " << (keyPressed->scancode == sf::Keyboard::Scancode::X ? "X" : "(other)") << "\n";
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                shouldExit = true;
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                y_camera -= 1.0f;
                this->g_engine.set_camera(x_camera,y_camera);
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                y_camera += 1.0f;
                this->g_engine.set_camera(x_camera,y_camera);
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                x_camera -= 1.0f;
                g_engine.set_camera(x_camera,y_camera);
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                x_camera += 1.0f;
                g_engine.set_camera(x_camera,y_camera);
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::E) {
                //open inventory
            }
        }else if (event->is<sf::Event::MouseWheelScrolled>()) {
            const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>();
            float delta = scroll->delta;
            float zoomFactor=delta>0?0.9:1.1;
            zoomLevel *= zoomFactor;
            constexpr float min_zoom_level=0.7f;
            constexpr float max_zoom_level=20.f;
            bool should_zoom=zoomLevel<max_zoom_level && zoomLevel>min_zoom_level;
            zoomLevel=std::max(min_zoom_level,std::min(zoomLevel,max_zoom_level));
            std::cout<<zoomLevel<<std::endl;
            if (should_zoom) {
                camera.zoom(zoomFactor);
            }
            window.setView(camera);
            g_engine.set_zoom(zoomLevel);
        }
    }
    if (shouldExit) {
        this->window.close();
        return;
    }
}

void game_engine::init() {
    std::cout<<"Init\n";
    this->g_engine.load_texture(0,"../assets/configuration files/texture_config.txt");
    this->init_window();
    this->init_cameras();
}
void game_engine::run() {
    std::cout<<"Running\n";
    while(this->window.isOpen()) {
        this->compute_dt();
        this->print_fps();
        this->process_events();
        this->update(dt);
        this->render();
    }
}
