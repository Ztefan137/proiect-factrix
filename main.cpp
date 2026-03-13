#include <iostream>
#include <array>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "include/graphic_functions.h"
#include "src/world_generator.h"
//////////////////////////////////////////////////////////////////////
void render_logic(sf::RenderWindow& window_obj){
        rect(window_obj,0,0,10000,10000,sf::Color::White);
        rect(window_obj,100,100,200,200,sf::Color::Red);
        //draw_chunks();
}



int main() {

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktop.size.x;
    unsigned int screenHeight = desktop.size.y;

    /*color_scheme default_scheme=color_scheme();
    default_scheme.window_dark_margin=sf::Color(0x0a,0x0a,0x0a,0xff);
    default_scheme.window_light_margin=sf::Color(0x3a,0x3a,0x3a,0xff);
    default_scheme.window_color=sf::Color(0x2a,0x2a,0x2a,0xff);
    ui_window test_ui(screenWidth/2.f,screenHeight/2,700,450,default_scheme);*/

    sf::Texture texture;
    if (!texture.loadFromFile("assets/dirt.png")) {
        std::cout<<"error";
    }

    sf::Sprite sprite(texture);

    // Desired size
    float targetWidth = 150.f;
    float targetHeight = 150.f;

    // Original size
    sf::Vector2u texSize = texture.getSize();

    // Compute scale factors
    float scaleX = targetWidth / texSize.x;
    float scaleY = targetHeight / texSize.y;

    sprite.setScale({scaleX, scaleY});

    std::vector<sf::sprite> sprites;
    sprites.push_back(sprite);
    world_generator generator();
    chunk test(0,0,generator);


    sf::RenderWindow window;
    window.create(sf::VideoMode({screenWidth, screenHeight}), "My Window", sf::State::Fullscreen);

    std::cout << "Fereastra a fost creată\n";
    window.setVerticalSyncEnabled(true);
    /// window.setFramerateLimit(60);

    while(window.isOpen()) {
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
                }
            }
        }
        if(shouldExit) {
            window.close();
            std::cout << "Fereastra a fost închisă (shouldExit == true)\n";
            break;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();
        render_logic(window);
        test.render(window,0,0,30,)
        //test_ui.render(window);
        window.display();
    }

    std::cout << "Programul a terminat execuția\n";
    return 0;
}