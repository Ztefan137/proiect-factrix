//
// Created by stefa on 4/6/2026.
//

#include "event_handler.h"
#include <iostream>
#include "player.h"
#include "key_event.h"
#include "mouse_event.h"
#include "ui_event.h"

#include "ui_binder.h"

#include "item.h"

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
                ui_binder inventory_binder;
                inventory_binder.set<item>("inventory_pointer",player.get_inventory());
                ui_event open_event(0,&inventory_binder);
                graphic_engine.process_event(&open_event);
                key_event curr_event("e");
                graphic_engine.process_event(&curr_event);
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Q) {
                player.add_item("furnace",10);
            }
        }else if (event->is<sf::Event::MouseWheelScrolled>()) {
            const auto* scroll = event->getIf<sf::Event::MouseWheelScrolled>();
            float delta = scroll->delta;
            graphic_engine.zoom(delta);
        }else if (event->is<sf::Event::MouseButtonPressed>()) {
            const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>();
            if (mouseClick->button == sf::Mouse::Button::Left) {
                sf::Vector2i mousePos = mouseClick->position;
                mouse_event curr_event(mousePos.x, mousePos.y,true,nullptr);
                graphic_engine.process_event(&curr_event);
            }else if (mouseClick->button == sf::Mouse::Button::Right) {
                sf::Vector2i mousePos = mouseClick->position;
                mouse_event curr_event(mousePos.x, mousePos.y,true,nullptr);
            }
        }
    }
    if (shouldExit) {
        window.close();
    }
    while (auto event=graphic_engine.get_event()) {
        std::cout<<"hello";
        graphic_engine.process_event(event);
        delete event;
    }
}

