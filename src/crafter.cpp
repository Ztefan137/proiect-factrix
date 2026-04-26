//
// Created by stefa on 4/25/2026.
//

#include "../include/crafter.h"
#include "../include/string_functions.h"
#include <fstream>

void crafter::bind_items(std::vector<item> *items) {
    this->items = items;
}

void crafter::craft() {
    if (crafting_progress > 0.f) {
        crafting_progress -= 0.1f;
        if (crafting_progress <= 0.f) {
            this->inventory_add(crafted_item);
            crafting_progress=0.f;
        }
    }
}

void crafter::init_craft(item item) {
    if (can_craft(item.get_name())) {
        auto it = recipes.find(item.get_name());
        for (auto &req: it->second) {
            inventory_take(req);
        }
        crafting_progress=1.f;
        crafted_item=item;
    }
}

bool crafter::can_craft(std::string item){
    if (this->crafting_progress>0.f) {
        return false;
    }
    auto it = recipes.find(item);
    if (it == recipes.end()) return false;
    for (auto& req : it->second) {
        int have = 0;
        for (auto& inv : *items)
            if (inv.get_name() == req.get_name())
                have += inv.get_quantity();

        if (have < req.get_quantity()){
            return false;
        }
    }
    return true;
}

void crafter::init_recipes(const std::string &config_file) {
    recipes.clear();
    std::ifstream file(config_file);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        auto parts = st::split(line, ':');
        if (parts.size() < 2) continue;

        std::string output = st::trim(parts[0]);
        std::string inputs = st::trim(parts[1]);

        std::vector<item> ing;
        auto tokens = st::split(inputs, ',');

        for (auto& t : tokens) {
            t = st::trim(t);
            if (t.empty()) continue;

            auto seg = st::split(t, ' ');
            if (seg.size() < 2) continue;

            ing.push_back({ seg[0], std::stoi(seg[1]) });
        }
        recipes[output] = ing;
    }
}

void crafter::inventory_take(item item) {
    while (item.get_quantity()>0) {
        for (auto& it : *items) {
            if (it.get_name() == item.get_name()) {
                it.take_quantity(item.get_quantity());
                item.take_quantity(item.get_quantity());
            }
        }
    }
}

void crafter::inventory_add(item item) {
    while (item.get_quantity()>0) {
        for (auto& inv : *items) {
            if (inv.get_name() == item.get_name()) {
                inv.add_quantity(item.get_quantity());
                item.take_quantity(item.get_quantity());
            }
        }
        for (auto& inv : *items) {
            if (inv.get_quantity() == 0 || inv.get_name() == "") {
                inv = item;
                item.take_quantity(item.get_quantity());
            }
        }
    }
}

