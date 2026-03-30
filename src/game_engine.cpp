//
// Created by stefa on 3/18/2026.
//

#include "../include/game_engine.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "../include/graphic_functions.h"

game_engine::game_engine() : g_engine(loader,window){

}
void game_engine::init() {
    std::cout<<"Init\n";
//    this->load_texture(1,"test_config");
    this->g_engine.load_texture(0,"default");
}
void game_engine::run() {
    std::cout<<"Running\n";
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;
    this->window.create(sf::VideoMode({screenWidth, screenHeight}), "My Window", sf::State::Fullscreen);

    sf::Vector2u windowSize = window.getSize();
    float aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    float worldHeight = 1000.f;
    float worldWidth  = worldHeight * aspectRatio;

    float x_camera = 0.0f;
    float y_camera = 0.0f;
    sf::View camera(sf::FloatRect({0, 0}, {worldWidth, worldHeight}));
    float zoomLevel=1.f;

    const float ui_width  = 2880.f;
    const float ui_height = 1800.f;

    //const float ui_width  = 1920.f;
    //const float ui_height = 1080.f;

    sf::View ui_camera(sf::FloatRect({0, 0}, {ui_width, ui_height}));
    ui_camera.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));
    ui_camera.setCenter({screenWidth / 2.f, screenHeight / 2.f});

    window.setVerticalSyncEnabled(true);

    window.setView(camera);
    g_engine.set_camera(x_camera,y_camera);
    g_engine.set_zoom(zoomLevel);

    sf::Clock clock;
    float fps = 0.f;

    while(this->window.isOpen()) {

        float dt = clock.restart().asSeconds();   // time since last frame
        fps = 1.f / dt;

        std::cout << "FPS: " << fps << "\n";

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
            break;
        }

        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        auto tileX = static_cast<float>(static_cast<int>((worldPos.x) / 32));
        auto tileY = static_cast<float>(static_cast<int>((worldPos.y) / 32));

        //g_engine.set_camera(x_camera, y_camera);

        //this->l_handler.run();
        window.clear(sf::Color::White);
        window.setView(camera);
        this->g_engine.draw_chunks();
        rect(window,tileX*32,tileY*32,(tileX+1)*32,(tileY+1)*32,sf::Color::White);
        window.setView(ui_camera);
        this->g_engine.render_uis();
        window.setView(camera);
        window.display();
    }
}
