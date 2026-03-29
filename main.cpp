#include <iostream>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "include/graphic_engine_functions.h"
#include "include/graphic_functions.h"
#include "include/world_generator.h"
#include "include/chunk.h"
#include "include/graphic_engine.h"
#include "include/chunk_loader.h"
#include "include/game_engine.h"
/////////////////////////////////////////////////////////////////////////

/*
int main(){

    game_engine game_engine;
    game_engine.load_texture(0,"default");

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;

    /*color_scheme default_scheme=color_scheme();
    default_scheme.window_dark_margin=sf::Color(0x0a,0x0a,0x0a,0xff);
    default_scheme.window _light_margin=sf::Color(0x3a,0x3a,0x3a,0xff);
    default_scheme.window_color=sf::Color(0x2a,0x2a,0x2a,0xff);
    ui_window test_ui(screenWidth/2.f,screenHeight/2,700,450,default_scheme);*/

    //std::vector<sf::Sprite> sprites;
    //std::vector<sf::Texture> textures;

    /*sf::Texture texture_atlas;
    texture_atlas.loadFromFile("assets/tiles.png");
    texture_atlas.setSmooth(false);*/

    /*world_generator generator;
    generator.set_seed(321);
    chunk_loader default_loader(generator);

    std::map<std::string, chunk> chunk_cache;

    float x_camera=20;
    float y_camera=20;

    float tile_scale=100.0f;


    sf::RenderWindow window;
    window.create(sf::VideoMode({screenWidth, screenHeight}), "My Window", sf::State::Fullscreen);
    //window.create(sf::VideoMode({screenWidth, screenHeight}), "My Window", sf::Style::Default);

    graphic_engine engine(default_loader,texture_atlas,window);

    sf::Vector2u windowSize = window.getSize();
    float aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    float worldHeight = 1000.f;
    float worldWidth  = worldHeight * aspectRatio;

    sf::View camera(sf::FloatRect({0, 0}, {worldWidth, worldHeight}));
    float zoomLevel=1.f;
    //std::cout << "Fereastra a fost creată\n";
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);
    window.setView(camera);
    engine.set_camera(x_camera,y_camera);
    engine.set_zoom(zoomLevel);
    sf::Clock clock;
    float fps = 0.f;

    while(window.isOpen()) {
        float dt = clock.restart().asSeconds();   // time since last frame
        fps = 1.f / dt;

        std::cout << "FPS: " << fps << "\n";
        bool shouldExit = false;

        while(const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                std::cout << "Fereastra a fost închisă\n";
            }
            else if (event->is<sf::Event::Resized>()) {
                std::cout << "New width: " << window.getSize().x << '\n'
                          << "New height: " << window.getSize().y << '\n';
            }
            else if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                std::cout << "Received key " << (keyPressed->scancode == sf::Keyboard::Scancode::X ? "X" : "(other)") << "\n";
                if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    shouldExit = true;
                }else if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                    //y_camera -= 1.0f;
                    //wd.set_camera(x_camera,y_camera);
                }else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                    y_camera += 1.0f;
                    engine.set_camera(x_camera,y_camera);
                }else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                    x_camera -= 1.0f;
                    engine.set_camera(x_camera,y_camera);
                }else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                    x_camera += 1.0f;
                    engine.set_camera(x_camera,y_camera);
                }
            }else if (event->is<sf::Event::MouseWheelScrolled>()) {
                const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>();
                float delta = scroll->delta;
                float zoomFactor=delta>0?0.9:1.1;
                if (delta>0) {
                    zoomLevel *= zoomFactor;
                    camera.zoom(zoomFactor);

                    window.setView(camera);
                    engine.set_zoom(zoomLevel);

                } else {
                    zoomLevel *= zoomFactor;
                    camera.zoom(zoomFactor);

                    window.setView(camera);
                    engine.set_zoom(zoomLevel);
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
                y_camera -= 1.0f;
                engine.set_camera(x_camera, y_camera);
            }
        }
        if(shouldExit) {
            window.close();
            std::cout << "Fereastra a fost închisă (shouldExit == true)\n";
            break;
        }

        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        int tileX = static_cast<int>(worldPos.x) / 32;
        int tileY = static_cast<int>(worldPos.y) / 32;

        engine.set_camera(x_camera, y_camera);

        window.clear(sf::Color::White);
        //render_logic(window,x_camera,y_camera,100,generator,sprites,chunk_cache,texture_atlas,zoomLevel);
        render_logic(engine);
        rect(window,tileX*32,tileY*32,(tileX+1)*32,(tileY+1)*32,sf::Color::White);
        //test_ui.render(window);
        window.display();
    }

    std::cout << "Programul a terminat execuția\n";
    return 0;
}*/
int main() {
    game_engine engine;
    engine.init();
    engine.run();
}
