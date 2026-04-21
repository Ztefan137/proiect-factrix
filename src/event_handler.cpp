//
// Created by stefa on 4/6/2026.
//

#include "event_handler.h"
#include <iostream>

#include "entity_data.h"
#include "furnace_prototype.h"
#include "player.h"
#include "key_event.h"
#include "mouse_event.h"
#include "ui_event.h"

#include "ui_binder.h"

#include "item.h"
#include "structures.h"

void event_handler::process_events(sf::RenderWindow &window,graphic_engine &graphic_engine,build_system& build_system,chunk_loader& loader,player& player,machine_handler &machines) {
    bool shouldExit = false;
    while(const std::optional curr_event = window.pollEvent()) {
        if (curr_event->is<sf::Event::Closed>()) {
            window.close();
            std::cout << "Fereastra a fost închisă\n";
        }
        else if (curr_event->is<sf::Event::KeyPressed>()) {
            const auto* keyPressed = curr_event->getIf<sf::Event::KeyPressed>();
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                if (graphic_engine.game_rendering_state() == 1) {
                    if (graphic_engine.get_ui_system().visible_uis()) {
                        graphic_engine.get_ui_system().close_uis();
                        machines.close_machines();
                    }else {
                        graphic_engine.stop_game_rendering();
                        generic_event<ui_idx_info> event({2});
                        graphic_engine.process_event(&event);
                    }
                }else{
                    shouldExit = true;
                }
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                player.move(0,-1,loader);
                graphic_engine.set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                player.move(0,1,loader);
                graphic_engine.set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                player.move(-1,0,loader);
                graphic_engine.set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                player.move(1,0,loader);
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
            else if (keyPressed->scancode == sf::Keyboard::Scancode::LShift) {
                build_system.set_on(false);
            }
        }else if (curr_event->is<sf::Event::MouseWheelScrolled>()) {
            const auto* scroll = curr_event->getIf<sf::Event::MouseWheelScrolled>();
            float delta = scroll->delta;
            graphic_engine.zoom(delta);
        }else if (curr_event->is<sf::Event::MouseButtonReleased>()) {
            const auto* mouseClick = curr_event->getIf<sf::Event::MouseButtonReleased>();
            if (mouseClick->button == sf::Mouse::Button::Left) {
                if (build_system.get_on()) {
                    build_system.build();
                }else {
                    sf::Vector2i mousePos = mouseClick->position;

                    //putem sa luam aici pozitia si sa verificam la ce tile ne uitam
                    if (!graphic_engine.get_ui_system().ui_at_coords(mousePos.x, mousePos.y)) {
                        sf::Vector2f world_pos = graphic_engine.get_mouse_coords();
                        std::cout<<"here"<<std::endl;
                        const int tile_size=64;
                        entity_data data;
                        int tileX=0;
                        int tileY=0;
                        int tile=0;
                        int entityX=0;
                        int entityY=0;
                        for (int i=0;i<3;i++) {
                            for (int j=0;j<3;j++) {
                                tileX = ((world_pos.x) / tile_size)+player.get_x()-23+i;
                                tileY = ((world_pos.y) / tile_size)+player.get_y()-15+j;
                                tile=loader.peak_tile(tileX,tileY,"buildings");
                                if (data.get_by_id(tile).buildable && data.get_by_id(tile).width > i && data.get_by_id(tile).height > j) {
                                    break;
                                }
                            }
                            if (data.get_by_id(tile).buildable && data.get_by_id(tile).width > i) {
                                break;
                            }
                        }
                        if (data.get_by_id(tile).buildable) {
                            if (data.get_by_id(tile).name == "furnace"){
                                ui_binder furnace_binder;
                                furnace_binder.set<item>("inventory_pointer",player.get_inventory());
                                machines.open_machine(tileX,tileY);
                                machine* interacted_machine=(machines.get_machine(tileX,tileY));
                                std::cout<<dynamic_cast<furnace_prototype*>(interacted_machine)->get_fuel()<<" "<<dynamic_cast<furnace_prototype*>(interacted_machine)->get_source()<<" "<<dynamic_cast<furnace_prototype*>(interacted_machine)->get_destination()<<std::endl;
                                furnace_binder.set<item>("fuel_pointer",dynamic_cast<furnace_prototype*>(interacted_machine)->get_fuel());
                                furnace_binder.set<item>("source_pointer",dynamic_cast<furnace_prototype*>(interacted_machine)->get_source());
                                furnace_binder.set<item>("destination_pointer",dynamic_cast<furnace_prototype*>(interacted_machine)->get_destination());
                                ui_event open_event(1,&furnace_binder);
                                graphic_engine.process_event(&open_event);
                                generic_event<ui_idx_info> curr_event({data.get_by_id(tile).ui_idx});
                                graphic_engine.process_event(&curr_event);
                            }
                        }
                    }else{
                        mouse_event curr_event(mousePos.x, mousePos.y,true,nullptr);
                        graphic_engine.process_event(&curr_event);
                    }
                }
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
        if (dynamic_cast<generic_event<build_mode_info>*>(event)) {
            int curr_building=dynamic_cast<generic_event<build_mode_info>*>(event)->get_event_data().current_building;
            entity_data data;
            if (data.get_by_id(curr_building).buildable){
                build_system.set_on(true);
                build_system.set_item(data.get_by_id(curr_building).name);
                key_event curr_event("e");
                graphic_engine.process_event(&curr_event);
            }
        }else if (dynamic_cast<generic_event<item_move_data>*>(event)){
            std::string item=dynamic_cast<generic_event<item_move_data>*>(event)->get_event_data().name;
            machines.process_event(event);
        }else if (dynamic_cast<generic_event<simple_event_data>*>(event)){
            int event_id=dynamic_cast<generic_event<simple_event_data>*>(event)->get_event_data().event_id;
            if (event_id == 1) {
                graphic_engine.start_game_rendering();
                graphic_engine.get_ui_system().close_uis();
            }
        }else{
            graphic_engine.process_event(event);
        }
        delete event;
    }
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    mouse_event curr_event(mousePos.x, mousePos.y,false,nullptr);
    graphic_engine.process_event(&curr_event);
}