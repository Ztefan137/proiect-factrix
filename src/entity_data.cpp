#include "entity_data.h"

#include <iostream>
#include <ostream>

const entity_data_prototype& entity_data::get_by_name(const std::string& name) {
    auto it = name_map().find(name);
    if (it == name_map().end()) {
        static entity_data_prototype dummy{};
        return dummy;
    }
    return it->second;
}

const entity_data_prototype& entity_data::get_by_id(int id) {
    auto it = id_map().find(id);
    if (it == id_map().end()) {
        static entity_data_prototype dummy{};
        return dummy;
    }
    return it->second;
}

void entity_data::init(){
    if (initialized()) {
        return;
    }

add({0,  "water",    1,1, 1,1, true,  false, "../assets/ground_tiles/water.jpg"});
add({1,  "dirt1",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt2.png"});
add({2,  "sand",     1,1, 1,1, false, false, "../assets/ground_tiles/sand3.png"});
add({3,  "dirt2",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt.png"});
add({4,  "dirt3",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt5.png"});
add({5,  "salt",     1,1, 1,1, false, false, "../assets/ground_tiles/salt.png"});
add({6,  "coal",     1,1, 1,1, false, false, "../assets/decoratives/coal.png"});
add({7,  "copper",   1,1, 1,1, false, false, "../assets/decoratives/copper.png"});
add({8,  "iron",     1,1, 1,1, false, false, "../assets/decoratives/iron.png"});
add({9,  "tree",     1,1, 2,3, true,  false, "../assets/decoratives/tree.png"});
add({10, "furnace",  2,2, 2,2, true,  true,  "../assets/buildings/furnace.png"});
add({11, "player",   1,1, 1,2, false, false, "../assets/player/engineer.png"});

add({20, "dirt0",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt0.png"});
add({21, "dirt1",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt1.png"});
add({22, "dirt2",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt2.png"});
add({23, "dirt3",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt3.png"});
add({24, "dirt4",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt4.png"});
add({25, "dirt5",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt5.png"});
add({26, "dirt6",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt6.png"});
add({27, "dirt7",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt7.png"});
add({28, "dirt8",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt8.png"});
add({29, "dirt9",    1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt9.png"});
add({30, "dirt10",   1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt10.png"});
add({31, "dirt11",   1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt11.png"});
add({32, "dirt12",   1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt12.png"});
add({33, "dirt13",   1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt13.png"});
add({34, "dirt14",   1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt14.png"});
add({35, "dirt15",   1,1, 1,1, false, false, "../assets/ground_tiles/dirt/dirt15.png"});



    initialized() = true;
}

void entity_data::add(const entity_data_prototype& data) {
    if (initialized())
        return;
    name_map()[data.name] = data;
    id_map()[data.id] = data;
}

std::unordered_map<std::string,entity_data_prototype>& entity_data::name_map() {
    static std::unordered_map<std::string, entity_data_prototype> m;
    return m;
}

std::unordered_map<int,entity_data_prototype>& entity_data::id_map() {
    static std::unordered_map<int, entity_data_prototype> m;
    return m;
}

bool& entity_data::initialized() {
    static bool flag = false;
    return flag;
}
