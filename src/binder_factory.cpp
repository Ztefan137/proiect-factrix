//
// Created by stefa on 5/17/2026.
//

#include "binder_factory.h"

#include "drill_prototype.h"
#include "furnace_prototype.h"
#include "player.h"

bool binder_factory::create_binder(ui_binder &binder, std::string type,game_session& session){
    player& player_reference=session.expose<player&>("player");
    if (type == "inventory") {
        binder.set<item>("inventory_pointer",player_reference.get_inventory());
        binder.set<item>("crafting_grid_pointer",player_reference.get_crafting_grid());
        return true;
    }
    return false;
}

bool binder_factory::create_binder(ui_binder &binder, std::string type,game_session& session,int tile_x,int tile_y){
    player& player_reference=session.expose<player&>("player");
    machine_handler& machines_reference=session.expose<machine_handler&>("machine_handler");
    if (type == "furnace") {
        machines_reference.open_machine(tile_x,tile_y);
        machine* interacted_machine=machines_reference.get_machine(tile_x,tile_y);
        binder.set<item>("inventory_pointer",player_reference.get_inventory());
        binder.set<item>("fuel_pointer",dynamic_cast<furnace_prototype*>(interacted_machine)->get_fuel());
        binder.set<item>("source_pointer",dynamic_cast<furnace_prototype*>(interacted_machine)->get_source());
        binder.set<item>("destination_pointer",dynamic_cast<furnace_prototype*>(interacted_machine)->get_destination());
        binder.set<float>("smelting_progress",dynamic_cast<furnace_prototype*>(interacted_machine)->get_progress());
        binder.set<float>("curr_fuel",dynamic_cast<furnace_prototype*>(interacted_machine)->get_curr_fuel());
        return true;
    }if (type == "drill") {
        ui_binder drill_binder;
        machines_reference.open_machine(tile_x,tile_y);
        machine* interacted_machine=(machines_reference.get_machine(tile_x,tile_y));
        binder.set<item>("inventory_pointer",player_reference.get_inventory());
        binder.set<item>("fuel_pointer",dynamic_cast<drill_prototype*>(interacted_machine)->get_fuel());
        binder.set<item>("destination_pointer",dynamic_cast<drill_prototype*>(interacted_machine)->get_destination());
        binder.set<float>("mining_progress",dynamic_cast<drill_prototype*>(interacted_machine)->get_progress());
        binder.set<float>("curr_fuel",dynamic_cast<drill_prototype*>(interacted_machine)->get_curr_fuel());
        return true;
    }
    return false;
}

