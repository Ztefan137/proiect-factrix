//
// Created by stefa on 3/13/2026.
//

#ifndef OOP_UI_H
#define OOP_UI_H
#include <vector>

class ui{
    float x,y;
    float width,height;
    float visibility;
    std::vector<ui> sub_uis;
    ui();
    ui(float x,float y,float width,float height);
    void add_sub_ui(const ui& new_sub_ui);
};


#endif //OOP_UI_H