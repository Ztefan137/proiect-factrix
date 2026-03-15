#include <iostream>
#include <array>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "include/graphic_engine_functions.h"
#include "include/graphic_functions.h"
#include "include/world_generator.h"
#include "include/chunk.h"
//////////////////////////////////////////////////////////////////////
void render_logic(sf::RenderWindow& window_obj,float x_camera,float y_camera,float scale_factor,world_generator& world_generator,std::vector<sf::Sprite>& sprites,std::map<std::string, chunk>& chunk_cache,sf::Texture& texture){
        rect(window_obj,100,100,200,200,sf::Color::Red); //test
        draw_chunks(window_obj,x_camera,y_camera,scale_factor,world_generator,texture,chunk_cache);
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

    sf::RenderTexture rt({64,32});
    rt.clear(sf::Color::Transparent);

    sf::RectangleShape redRect({100.f, 100.f});
    redRect.setFillColor(sf::Color::Red);
    redRect.setPosition({0.f, 0.f});
    redRect.setSize({32.f,32.f});

    sf::RectangleShape blueRect({100.f, 100.f});
    blueRect.setFillColor(sf::Color::Blue);
    blueRect.setPosition({32.f, 0.f});
    redRect.setSize({32.f,32.f});

    rt.draw(redRect);
    rt.draw(blueRect);

    sf::Texture texture_atlas = rt.getTexture();

    world_generator generator;

    std::map<std::string, chunk> chunk_cache;

    float x_camera=20;
    float y_camera=20;

    float tile_scale=100.0f;


    sf::RenderWindow window;
    //window.create(sf::VideoMode({screenWidth, screenHeight}), "My Window", sf::State::Fullscreen);
    window.create(sf::VideoMode({screenWidth, screenHeight}), "My Window", sf::Style::Default);

    std::cout << "Fereastra a fost creată\n";
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);
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
                }else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                    y_camera += 1.0f;
                }else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                    x_camera -= 1.0f;
                }else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                    x_camera += 1.0f;
                }
            }else if (event->is<sf::Event::MouseWheelScrolled>()) {
                const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>();
                float delta = scroll->delta;
                if (delta>0) {
                    tile_scale+=20;
                    set_scale(textures,sprites,tile_scale);
                } else {
                    tile_scale-=20;
                    set_scale(textures,sprites,tile_scale);
                }
            }
        }
        if(shouldExit) {
            window.close();
            std::cout << "Fereastra a fost închisă (shouldExit == true)\n";
            break;
        }

        window.clear(sf::Color::White);
        render_logic(window,x_camera,y_camera,100,generator,sprites,chunk_cache,texture_atlas);
        //test_ui.render(window);
        window.display();
    }

    std::cout << "Programul a terminat execuția\n";
    return 0;
}