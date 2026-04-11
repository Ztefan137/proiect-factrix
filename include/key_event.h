//
// Created by stefa on 4/6/2026.
//

#ifndef OOP_KEY_EVENT_H
#define OOP_KEY_EVENT_H
#include "../include/event.h"
#include <string>

class key_event : public event{
    std::string type="key_event";
    std::string key="";
public:
    key_event(std::string key);
};


#endif //OOP_KEY_EVENT_H