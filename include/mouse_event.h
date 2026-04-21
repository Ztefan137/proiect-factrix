//
// Created by stefa on 4/14/2026.
//

#ifndef OOP_MOUSE_EVENT_H
#define OOP_MOUSE_EVENT_H
#include "event.h"
#include "SFML/Graphics.hpp"

class mouse_event : public event{
    std::string type="key_event";
    float mouse_x,mouse_y;
    sf::View* view=nullptr;
    bool clicked=false;
public:
    mouse_event(float mouse_x,float mouse_y,bool clicked,sf::View* view);
    float get_mouse_x();
    float get_mouse_y();
    void set_view(sf::View* view);
    sf::View* get_view();
    bool is_clicked();
};


#endif //OOP_MOUSE_EVENT_H