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
#include "../../include/binder_factory.h"

void event_handler::process_events(sf::RenderWindow &window,graphic_engine &graphic_engine,game_session& session) {

    build_system &build_system_reference=session.expose<build_system&>("build_system");
    chunk_loader &loader_reference=session.expose<chunk_loader&>("loader");
    player &player_reference=session.expose<player&>("player");
    machine_handler &machines_reference=session.expose<machine_handler&>("machine_handler");

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
        }else if (curr_event->is<sf::Event::MouseButtonReleased>() ) {
            const auto* mouseClick = curr_event->getIf<sf::Event::MouseButtonReleased>();
            if (mouseClick->button == sf::Mouse::Button::Left) {
                build_system& build_system_reference=session.expose<build_system&>("build_system");
                if (build_system_reference.get_on()) {
                    build_system_reference.build();
                }else {
                    sf::Vector2i mousePos = mouseClick->position;
                    if (!graphic_engine.get_ui_system().ui_at_coords(mousePos.x, mousePos.y)) {
                        if (session.is_active()) {
                            int tileX=0;
                            int tileY=0;
                            int tile=0;
                            tile=graphic_engine.get_hovered_entity("buildings").id;
                            tileX=graphic_engine.get_hovered_entity("buildings").x;
                            tileY=graphic_engine.get_hovered_entity("buildings").y;
                            if (entity_data::get_by_id(tile).buildable) {
                                ui_binder binder;
                                if (binder_factory::create_binder(binder,entity_data::get_by_id(tile).name,session,tileX,tileY)){
                                    ui_event open_event(entity_data::get_by_id(tile).ui_idx,&binder);
                                    graphic_engine.process_event(&open_event);
                                    generic_event<ui_idx_info> event({entity_data::get_by_id(tile).ui_idx});
                                    graphic_engine.process_event(&event);
                                }
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
                build_system_reference.set_on(true);
                build_system_reference.set_item(data.get_by_id(curr_building).name);
                key_event curr_event("e");
                graphic_engine.process_event(&curr_event);
            }
        }else if (auto move_event=dynamic_cast<generic_event<item_move_data>*>(event)){
            entity_data data;
            if (data.get_by_name(move_event->get_event_data().to).buildable){
                std::string item=dynamic_cast<generic_event<item_move_data>*>(event)->get_event_data().name;
                machines_reference.process_event(event);
            }else{
                player_reference.add_item(move_event->get_event_data().source->get_name(),move_event->get_event_data().source->get_quantity());
                machines_reference.process_event(event);
            }
        }else if (dynamic_cast<generic_event<simple_event_data>*>(event)){
            int event_id=dynamic_cast<generic_event<simple_event_data>*>(event)->get_event_data().event_id;
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
    //build_system &build_system_reference=session.expose<build_system&>("build_system");
    chunk_loader &loader_reference=session.expose<chunk_loader&>("loader");
    player &player_reference=session.expose<player&>("player");
    //machine_handler &machines_reference=session.expose<machine_handler&>("machine_handler");
    if (session.is_active()) {
        int dx = 0;
        int dy = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){
            dy -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
            dy += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
            dx -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
            dx += 1;
        }
        if (dx != 0 || dy != 0) {
            generic_event<player_move_data> move_event({dx, dy});
            session.process_event(&move_event);

            graphic_engine.set_camera(player_reference.get_x(),player_reference.get_y());
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
            mining_info info;
            info.tile_x=graphic_engine.get_mouse_tile_coords().x;
            info.tile_y=graphic_engine.get_mouse_tile_coords().y;
            if ((info.tile_x-player_reference.get_x())*(info.tile_x-player_reference.get_x())+(info.tile_y-player_reference.get_y())*(info.tile_y-player_reference.get_y()) <= 9.f){
                int mined_decorative=loader_reference.peak_tile(info.tile_x, info.tile_y,"decoratives");
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
                    }
                }
            }
        }
    }
}
