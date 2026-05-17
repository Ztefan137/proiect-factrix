//
// Created by stefa on 4/6/2026.
//

#include "event_handler.h"
#include <iostream>

#include "drill_prototype.h"
#include "entity_data.h"
#include "furnace_prototype.h"
#include "game_session.h"
#include "interface_layer.h"
#include "player.h"
#include "key_event.h"
#include "mouse_event.h"
#include "ui_event.h"

#include "ui_binder.h"

#include "item.h"
#include "structures.h"
#include "../binder_factory.h"

void event_handler::process_events(sf::RenderWindow &window,graphic_engine &graphic_engine,game_session& session) {
    while(const std::optional curr_event = window.pollEvent()) {
        if (curr_event->is<sf::Event::Closed>()) {
            window.close();
            std::cout << "Fereastra a fost închisă\n";
        }
        else if (curr_event->is<sf::Event::KeyPressed>()) {
            bool player_moved=false;
            const auto* keyPressed = curr_event->getIf<sf::Event::KeyPressed>();
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                if (graphic_engine.game_rendering_state() == 1) {
                    if (graphic_engine.get_ui_system().visible_uis()) {
                        graphic_engine.get_ui_system().close_uis();
                        generic_event<simple_event_text> event({"close_machines"});
                        session.process_event(&event);
                    }else {
                        graphic_engine.stop_game_rendering();
                        generic_event<ui_idx_info> event({2});
                        build_system& build_system_reference=session.expose<build_system&>("build_system");
                        build_system_reference.set_on(false);
                        graphic_engine.process_event(&event);
                    }
                }else{
                    window.close();
                }
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::E && session.is_active()) {
                //open inventory
                ui_binder inventory_binder;
                if (binder_factory::create_binder(inventory_binder,"inventory",session)) {
                    ui_event open_event(0,&inventory_binder);
                    graphic_engine.process_event(&open_event);
                    key_event curr_event("e");
                    graphic_engine.process_event(&curr_event);
                }
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Q && session.is_active()) {
                player& player_reference=session.expose<player&>("player");
                player_reference.add_item("furnace",10);
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::LShift && session.is_active()) {
                generic_event<simple_event_text> event({"build_system_off"});
                session.process_event(&event);
            }
        }else if (curr_event->is<sf::Event::MouseWheelScrolled>() && session.is_active()) {
            const auto* scroll = curr_event->getIf<sf::Event::MouseWheelScrolled>();
            float delta = scroll->delta;
            graphic_engine.zoom(delta);
            //graphic_engine.get_camera_system.zoom();
        }else if (curr_event->is<sf::Event::MouseButtonReleased>() ) {
            const auto* mouseClick = curr_event->getIf<sf::Event::MouseButtonReleased>();
            if (mouseClick->button == sf::Mouse::Button::Left) {
                build_system& build_system_reference=session.expose<build_system&>("build_system");
                if (build_system_reference.get_on()) {
                    build_system_reference.build();
                }else {
                    sf::Vector2i mousePos = mouseClick->position;

                    //putem sa luam aici pozitia si sa verificam la ce tile ne uitam
                    if (!graphic_engine.get_ui_system().ui_at_coords(mousePos.x, mousePos.y) && session.is_active()) {
                        entity_data data;
                        int tileX=0;
                        int tileY=0;
                        int tile=0;
                        tile=graphic_engine.get_hovered_entity("buildings").id;
                        tileX=graphic_engine.get_hovered_entity("buildings").x;
                        tileY=graphic_engine.get_hovered_entity("buildings").y;
                        if (entity_data::get_by_id(tile).buildable) {
                            ui_binder binder;
                            if (binder_factory::create_binder(binder,data.get_by_id(tile).name,session,tileX,tileY)){
                                ui_event open_event(entity_data::get_by_id(tile).ui_idx,&binder);
                                graphic_engine.process_event(&open_event);
                                generic_event<ui_idx_info> event({data.get_by_id(tile).ui_idx});
                                graphic_engine.process_event(&event);
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
    while (auto event=graphic_engine.get_event()) {
        if (dynamic_cast<generic_event<build_mode_info>*>(event)) {
            int curr_building=dynamic_cast<generic_event<build_mode_info>*>(event)->get_event_data().current_building;
            entity_data data;
            if (data.get_by_id(curr_building).buildable){
                build_system& build_system_reference=session.expose<build_system&>("build_system");
                build_system_reference.set_on(true);
                build_system_reference.set_item(data.get_by_id(curr_building).name);
                key_event curr_event("e");
                graphic_engine.process_event(&curr_event);
            }
        }else if (auto move_event=dynamic_cast<generic_event<item_move_data>*>(event)){
            entity_data data;
            player& player_reference=session.expose<player&>("player");
            machine_handler& machines_reference=session.expose<machine_handler&>("machines");
            if (data.get_by_name(move_event->get_event_data().to).buildable){
                std::string item=dynamic_cast<generic_event<item_move_data>*>(event)->get_event_data().name;
                machines_reference.process_event(event);
            }else{
                player_reference.add_item(move_event->get_event_data().source->get_name(),move_event->get_event_data().source->get_quantity());
                machines_reference.process_event(event);
            }
        }else if (dynamic_cast<generic_event<simple_event_data>*>(event)){
            int event_id=dynamic_cast<generic_event<simple_event_data>*>(event)->get_event_data().event_id;
            player& player_reference=session.expose<player&>("player");
            switch (event_id) {
                case 1:
                    graphic_engine.start_game_rendering();
                    graphic_engine.get_ui_system().close_uis();
                    srand(time(nullptr));
                    session.init(rand()%1000);
                    graphic_engine.set_camera(player_reference.get_x(), player_reference.get_y());
                    break;
                case 2:
                    graphic_engine.start_game_rendering();
                    graphic_engine.get_ui_system().close_uis();
                    session.load("../saves/last_save.txt");
                    graphic_engine.set_camera(player_reference.get_x(), player_reference.get_y());
                    break;
                case 93:
                    window.close();
                    break;
            }
        }else if (dynamic_cast<generic_event<crafting_event_data>*>(event)){
            std::cout<<"crafting";
            player& player_reference=session.expose<player&>("player");
            player_reference.craft(*dynamic_cast<generic_event<crafting_event_data>*>(event)->get_event_data().crafted);
        }else{
            graphic_engine.process_event(event);
        }
        delete event;
    }
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    mouse_event curr_event(mousePos.x, mousePos.y,false,nullptr);
    graphic_engine.process_event(&curr_event);
}

void event_handler::add_event(event *event) {
    this->event_queue.push(event);

}

void event_handler::process_tick_events(sf::RenderWindow &window, graphic_engine &graphic_engine,game_session& session) {
    build_system &build_system_reference=session.expose<build_system&>("build_system");
    chunk_loader &loader_reference=session.expose<chunk_loader&>("loader");
    player &player_reference=session.expose<player&>("player");
    machine_handler &machines_reference=session.expose<machine_handler&>("machine_handler");

    while(const std::optional curr_event = window.pollEvent()) {
        bool player_moved=false;
        const auto* keyPressed = curr_event->getIf<sf::Event::KeyPressed>();
        if (curr_event->is<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                generic_event<player_move_data> event({0,-1});
                session.process_event(&event);
                player_moved=true;
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                generic_event<player_move_data> event({0,1});
                session.process_event(&event);
                player_moved=true;
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                generic_event<player_move_data> event({-1,0});
                session.process_event(&event);
                player_moved=true;
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                generic_event<player_move_data> event({1,0});
                session.process_event(&event);
                player_moved=true;
            }
            if (player_moved) {
                player& player_reference=session.expose<player&>("player");
                graphic_engine.set_camera(player_reference.get_x(),player_reference.get_y());
            }
        }
        break;
    }


    if (session.is_active() || 1 == 1) {

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
            mining_info info;
            info.tile_x=graphic_engine.get_mouse_tile_coords().x;
            info.tile_y=graphic_engine.get_mouse_tile_coords().y;
//            info.tile_x = (graphic_engine.get_mouse_coords().x / graphic_engine.get_tile_size())+player_reference.get_x()-23;
//            info.tile_y= (graphic_engine.get_mouse_coords().y / graphic_engine.get_tile_size())+player_reference.get_y()-14;
            if ((info.tile_x-player_reference.get_x())*(info.tile_x-player_reference.get_x())+(info.tile_y-player_reference.get_y())*(info.tile_y-player_reference.get_y()) <= 9.f){
                int mined_decorative=loader_reference.peak_tile(static_cast<int>(info.tile_x), static_cast<int>(info.tile_y),"decoratives");
                if (*player_reference.get_mining_progress() == 0.f){
                    ui_binder mining_binder;
                    mining_binder.set<float>("mining_progress",player_reference.get_mining_progress());
                    event* mining_ui_open=new ui_event(3,&mining_binder);
                    graphic_engine.process_event(mining_ui_open);
                    event* mining_ui_event=new generic_event<ui_idx_info>({3});
                    graphic_engine.process_event(mining_ui_event);
                }
                player_reference.mine(0.02);
                if (player_reference.has_mined()) {
                    entity_data data;
                    if (mined_decorative == 6){
                        player_reference.add_item("coal_ore",1);
                    }else if (mined_decorative == 7) {
                        player_reference.add_item("copper_ore",1);
                    }else if (mined_decorative == 8) {
                        player_reference.add_item("iron_ore",1);
                    }else if (mined_decorative == 12) {
                        player_reference.add_item("rock",1);
                    }else{
                        /*std::string building=data.get_by_id(loader.peak_tile(static_cast<int>(mine_event->get_event_data().tile_x), static_cast<int>(mine_event->get_event_data().tile_y),"buildings")).name;
                        std::cout<<building<<std::endl;
                        if (building != "" && building != "player"){
                            machines.delete_machine(mine_event->get_event_data().tile_x,mine_event->get_event_data().tile_y);
                            player.add_item(building,1);
                        }*/
                    }
                }
            }

            //info.tile_x=graphic_engine.get_mouse_tiles().x;
            //info.tile_y=graphic_engine.get_mouse_tiles().y;
        }
    }
}
