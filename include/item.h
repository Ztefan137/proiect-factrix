//
// Created by stefa on 4/13/2026.
//

#ifndef OOP_ITEM_H
#define OOP_ITEM_H
#include <string>

class item {
    std::string name;
    int quantity;
public:
    item(std::string name, int quantity);
    std::string get_name();
    int get_quantity();
};


#endif //OOP_ITEM_H