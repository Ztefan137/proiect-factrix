//
// Created by stefa on 4/25/2026.
//

#ifndef OOP_CRAFTER_H
#define OOP_CRAFTER_H
#include <unordered_map>
#include <vector>
#include "item.h"

class crafter {
    float crafting_progress=0.f;
    std::vector<item>* items;
    item crafted_item;
    std::unordered_map<std::string,std::vector<item>> recipes;
public:
    crafter()=default;
    void bind_items(std::vector<item>* items);
    void init_recipes(const std::string& config_file);
    bool can_craft(std::string item);
        void init_craft(item item);
    void craft();
    void inventory_take(item item);
    void inventory_add(item item);
};


#endif //OOP_CRAFTER_H