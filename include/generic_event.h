//
// Created by stefa on 4/15/2026.
//

#ifndef OOP_GENERIC_EVENT_H
#define OOP_GENERIC_EVENT_H
#include "event.h"

template <typename event_data>
class generic_event :public event{
    std::string event_name;
    event_data data;
    public:
    generic_event(const event_data& data) : data(data) {}
    std::string getEventName();
};


#endif //OOP_GENERIC_EVENT_H