//
// Created by stefa on 4/6/2026.
//

#include "event_handler.h"
#include <iostream>
#include "player.h"

void event_handler::process_events(sf::RenderWindow &window,graphic_engine &graphic_engine,player& player) {
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
                player.move(0,-1);
                graphic_engine.set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                player.move(0,1);
                graphic_engine.set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                player.move(-1,0);
                graphic_engine.set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                player.move(1,0);
                graphic_engine.set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::E) {
                //open inventory
                graphic_engine.process_event("e");
            }
        }else if (event->is<sf::Event::MouseWheelScrolled>()) {
            const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>();
            float delta = scroll->delta;
            graphic_engine.zoom(delta);
        }
    }
    if (shouldExit) {
        window.close();
    }
}
