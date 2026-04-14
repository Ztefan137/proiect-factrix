//
// Created by stefa on 4/14/2026.
//

#ifndef OOP_MOUSE_EVENT_H
#define OOP_MOUSE_EVENT_H
#include "event.h"

class mouse_event : public event{
    std::string type="key_event";
    float mouse_x,mouse_y;
public:
    mouse_event(float mouse_x,float mouse_y);
    float get_mouse_x();
    float get_mouse_y();
};


#endif //OOP_MOUSE_EVENT_H