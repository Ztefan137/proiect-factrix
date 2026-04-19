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
    item()=default;
    item(std::string name, int quantity);
    std::string get_name() const;
    void set_name(std::string new_name);
    int get_quantity() const;
    void add_quantity(int d_quantity);
    void take_quantity(int d_quantity);
};


#endif //OOP_ITEM_H