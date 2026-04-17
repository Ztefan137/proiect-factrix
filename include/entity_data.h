//
// Created by stefa on 4/17/2026.
//

#ifndef OOP_ENTITY_DATA_H
#define OOP_ENTITY_DATA_H
#include <map>
#include <string>
#include "structures.h"
#include <unordered_map>

class entity_data {
public:
    static const entity_data_prototype& get_by_name(const std::string& name);
    static const entity_data_prototype& get_by_id(int id);
    static void init();

private:
    static void add(const entity_data_prototype& proto);
    static std::unordered_map<std::string, entity_data_prototype>& name_map();
    static std::unordered_map<int, entity_data_prototype>& id_map();
    static bool& initialized();
};


#endif //OOP_ENTITY_DATA_H