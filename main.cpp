#include <iostream>
#include <array>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "include/graphic_engine_functions.h"
#include "include/graphic_functions.h"
#include "include/world_generator.h"
#include "include/chunk.h"
#include "include/graphic_engine.h"
#include "include/chunk_loader.h"
//////////////////////////////////////////////////////////////////////
/*void render_logic(sf::RenderWindow& window_obj,float x_camera,float y_camera,float scale_factor,world_generator& world_generator,std::vector<sf::Sprite>& sprites,std::map<std::string, chunk>& chunk_cache,sf::Texture& texture,float zoom_level){
        rect(window_obj,100,100,200,200,sf::Color::Red); //test
        draw_chunks(window_obj,x_camera,y_camera,scale_factor,world_generator,texture,chunk_cache,zoom_level);
}*/
void render_logic(graphic_engine &engine) {
    engine.draw_chunks();
}
void tick_logic() {

}


int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;

    /*color_scheme default_scheme=color_scheme();
    default_scheme.window_dark_margin=sf::Color(0x0a,0x0a,0x0a,0xff);
    default_scheme.window_light_margin=sf::Color(0x3a,0x3a,0x3a,0xff);
    default_scheme.window_color=sf::Color(0x2a,0x2a,0x2a,0xff);
    ui_window test_ui(screenWidth/2.f,screenHeight/2,700,450,default_scheme);*/

    std::vector<sf::Sprite> sprites;
    std::vector<sf::Texture> textures;

    /*sf::Texture texture_atlas;
    texture_atlas.loadFromFile("assets/tiles.png");
    texture_atlas.setSmooth(false);*/

    sf::RenderTexture rt({32*6,32});
    rt.clear(sf::Color::Transparent);

    sf::RectangleShape redRect({100.f, 100.f});
    //redRect.setFillColor(sf::Color(0,150,0,255));
    redRect.setPosition({0.f, 0.f});
    sf::Texture redRect_texture;
    redRect_texture.loadFromFile("assets/water.jpg");
    redRect.setTexture(&redRect_texture);
    redRect.setSize({32.f,32.f});

    sf::RectangleShape blueRect({100.f, 100.f});
    blueRect.setPosition({32.f, 0.f});
    sf::Texture blueRect_texture;
    blueRect_texture.loadFromFile("assets/dirt2.png");
    blueRect.setTexture(&blueRect_texture);
    blueRect.setSize({32.f,32.f});

    sf::RectangleShape Rect2({100.f, 100.f});
    Rect2.setFillColor(sf::Color(255, 231, 163,255));
    Rect2.setPosition({32.f*2, 0.f});
    Rect2.setSize({32.f,32.f});

    sf::RectangleShape Rect3({100.f, 100.f});
    Rect3.setFillColor(sf::Color(207, 176, 89,255));
    Rect3.setPosition({32.f*3, 0.f});
    Rect3.setSize({32.f,32.f});

    sf::RectangleShape Rect4({100.f, 100.f});
    Rect4.setFillColor(sf::Color(87, 73, 35,255));
    Rect4.setPosition({32.f*4, 0.f});
    Rect4.setSize({32.f,32.f});

    sf::RectangleShape Rect5({100.f, 100.f});
    Rect5.setFillColor(sf::Color(115, 108, 91,255));
    Rect5.setPosition({32.f*5, 0.f});
    Rect5.setSize({32.f,32.f});

    rt.draw(redRect);
    rt.draw(blueRect);
    rt.draw(Rect2);
    rt.draw(Rect3);
    rt.draw(Rect4);
    rt.draw(Rect5);

    sf::Texture texture_atlas = rt.getTexture();

    world_generator generator;
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
                    y_camera -= 1.0f;
                    engine.set_camera(x_camera,y_camera);
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
        }
        if(shouldExit) {
            window.close();
            std::cout << "Fereastra a fost închisă (shouldExit == true)\n";
            break;
        }

        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        int tileX = static_cast<int>(worldPos.x) / 32;
        int tileY = static_cast<int>(worldPos.y) / 32;

        window.clear(sf::Color::White);
        //render_logic(window,x_camera,y_camera,100,generator,sprites,chunk_cache,texture_atlas,zoomLevel);
        render_logic(engine);
        rect(window,tileX*32,tileY*32,(tileX+1)*32,(tileY+1)*32,sf::Color::White);
        //test_ui.render(window);
        window.display();
    }

    std::cout << "Programul a terminat execuția\n";
    return 0;
}
