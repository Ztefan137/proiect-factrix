//
// Created by stefa on 5/15/2026.
//

#include "god_event_handler.h"

#include "drill_prototype.h"
#include "entity_data.h"
#include "key_event.h"
#include "mouse_event.h"
#include "ui_event.h"
#include <random>
#include <cstdlib>

god_event_handler::god_event_handler() {

}

void god_event_handler::process_events(sf::RenderWindow &window,graphic_engine &graphic_engine,game_session& session) {

    bool shouldExit = false;
    build_system &build_system_reference=session.expose<build_system&>("build_system");
    chunk_loader &loader_reference=session.expose<chunk_loader&>("loader");
    player &player_reference=session.expose<player&>("player");
    machine_handler &machines_reference=session.expose<machine_handler&>("machine_handler");
    while(const std::optional curr_event = window.pollEvent()) {
        if (curr_event->is<sf::Event::Closed>()) { //interface dependent
            window.close();
            std::cout << "Fereastra a fost închisă\n";
        }
        else if (curr_event->is<sf::Event::KeyPressed>()) { //interface dependent
            const auto* keyPressed = curr_event->getIf<sf::Event::KeyPressed>();
            if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                //asta nu e bine aici depinde de stari interne ale graphic_engine
                if (graphic_engine.game_rendering_state() == 1) {
                    if (graphic_engine.get_ui_system().visible_uis()) {
                        graphic_engine.get_ui_system().close_uis();
                        machines_reference.close_machines();
                    }else {
                        graphic_engine.stop_game_rendering();
                        generic_event<ui_idx_info> event({2});
                        graphic_engine.process_event(&event);
                        session.save("../saves/last_save.txt");
                    }
                }else{
                    shouldExit = true;
                }
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                //si astea sunt proaste deoarece n ar trebui sa se acceseze metode ale sistemelor
                //in primul rand nici nu ar trebui sa ai acces la player aici
                player_reference.move(0,-1,loader_reference);
                graphic_engine.set_camera(player_reference.get_x(),player_reference.get_y());
                //astea devin
                //game_session.process_event<player_move_event>;
                //graphic_engine.process_event<>
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                player_reference.move(0,1,loader_reference);
                graphic_engine.set_camera(player_reference.get_x(),player_reference.get_y());
                //graphic_engine.get_camera_system().set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                player_reference.move(-1,0,loader_reference);
                graphic_engine.set_camera(player_reference.get_x(),player_reference.get_y());
                //graphic_engine.get_camera_system().set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                player_reference.move(1,0,loader_reference);
                graphic_engine.set_camera(player_reference.get_x(),player_reference.get_y());
                //graphic_engine.get_camera_system().set_camera(player.get_x(),player.get_y());
            }else if (keyPressed->scancode == sf::Keyboard::Scancode::E) {
                //open inventory
                ui_binder inventory_binder;
                inventory_binder.set<item>("inventory_pointer",player_reference.get_inventory());
                inventory_binder.set<item>("crafting_grid_pointer",player_reference.get_crafting_grid());
                ui_event open_event(0,&inventory_binder);
                graphic_engine.process_event(&open_event);
                key_event curr_event("e");
                graphic_engine.process_event(&curr_event);
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Q) {
                player_reference.add_item("furnace",10);
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::LShift) {
                build_system_reference.set_on(false);
            }
        }else if (curr_event->is<sf::Event::MouseWheelScrolled>()) { //interface dependent
            const auto* scroll = curr_event->getIf<sf::Event::MouseWheelScrolled>();
            float delta = scroll->delta;
            graphic_engine.zoom(delta);
            //graphic_engine.get_camera_system.zoom();
        }else if (curr_event->is<sf::Event::MouseButtonReleased>()) {
            const auto* mouseClick = curr_event->getIf<sf::Event::MouseButtonReleased>();
            if (mouseClick->button == sf::Mouse::Button::Left) {
                if (build_system_reference.get_on()) {
                    build_system_reference.build();
                }else {
                    sf::Vector2i mousePos = mouseClick->position;

                    //putem sa luam aici pozitia si sa verificam la ce tile ne uitam
                    if (!graphic_engine.get_ui_system().ui_at_coords(mousePos.x, mousePos.y)) {
                        //sf::Vector2f world_pos = graphic_engine.get_mouse_coords();
                        //const int tile_size=64;
                        entity_data data;
                        int tileX=0;
                        int tileY=0;
                        int tile=0;
                        /*for (int i=0;i<3;i++) {
                            for (int j=0;j<3;j++) {
                                tileX = graphic_engine.get_mouse_tile_coords().x+i;
                                tileY = graphic_engine.get_mouse_tile_coords().y+j;
                                tile=loader.peak_tile(tileX,tileY,"buildings");
                                if (data.get_by_id(tile).buildable && data.get_by_id(tile).width > i && data.get_by_id(tile).height > j) {
                                    break;
                                }
                            }
                            if (data.get_by_id(tile).buildable && data.get_by_id(tile).width > i) {
                                break;
                            }
                        }*/
                        tile=graphic_engine.get_hovered_entity("buildings").id;
                        tileX=graphic_engine.get_hovered_entity("buildings").x;
                        tileY=graphic_engine.get_hovered_entity("buildings").y;
                        if (entity_data::get_by_id(tile).buildable){
                            if (data.get_by_id(tile).name == "furnace"){
                                ui_binder furnace_binder;
                                furnace_binder.set<item>("inventory_pointer",player_reference.get_inventory());
                                machines_reference.open_machine(tileX,tileY);
                                machine* interacted_machine=(machines_reference.get_machine(tileX,tileY));
                                furnace_binder.set<item>("fuel_pointer",dynamic_cast<furnace_prototype*>(interacted_machine)->get_fuel());
                                furnace_binder.set<item>("source_pointer",dynamic_cast<furnace_prototype*>(interacted_machine)->get_source());
                                furnace_binder.set<item>("destination_pointer",dynamic_cast<furnace_prototype*>(interacted_machine)->get_destination());
                                furnace_binder.set<float>("smelting_progress",dynamic_cast<furnace_prototype*>(interacted_machine)->get_progress());
                                furnace_binder.set<float>("curr_fuel",dynamic_cast<furnace_prototype*>(interacted_machine)->get_curr_fuel());
                                ui_event open_event(1,&furnace_binder);
                                graphic_engine.process_event(&open_event);
                                generic_event<ui_idx_info> curr_event({data.get_by_id(tile).ui_idx});
                                graphic_engine.process_event(&curr_event);
                            }
                            else if (data.get_by_id(tile).name == "drill"){
                                ui_binder drill_binder;
                                drill_binder.set<item>("inventory_pointer",player_reference.get_inventory());
                                machines_reference.open_machine(tileX,tileY);
                                machine* interacted_machine=(machines_reference.get_machine(tileX,tileY));
                                drill_binder.set<item>("fuel_pointer",dynamic_cast<drill_prototype*>(interacted_machine)->get_fuel());
                                drill_binder.set<item>("destination_pointer",dynamic_cast<drill_prototype*>(interacted_machine)->get_destination());
                                drill_binder.set<float>("mining_progress",dynamic_cast<drill_prototype*>(interacted_machine)->get_progress());
                                drill_binder.set<float>("curr_fuel",dynamic_cast<drill_prototype*>(interacted_machine)->get_curr_fuel());
                                ui_event open_event(4,&drill_binder);
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
                    shouldExit=true;
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
    while (!this->event_queue.empty()) {
        auto event=this->event_queue.front();
        if (auto mine_event=dynamic_cast<generic_event<mining_info>*>(event)) {
        }
        delete event;
        this->event_queue.pop();
    }

    //hover
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    mouse_event curr_event(mousePos.x, mousePos.y,false,nullptr);
    graphic_engine.process_event(&curr_event);

    if (shouldExit) {
        window.close();
    }
}
