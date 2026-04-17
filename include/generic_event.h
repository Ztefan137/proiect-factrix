#ifndef OOP_GENERIC_EVENT_H
#define OOP_GENERIC_EVENT_H

#include "event.h"
#include <string>

template <typename event_data>
class generic_event : public event {
    std::string event_name;
    event_data data;

public:
    generic_event(const event_data& data) : data(data) {}

    std::string getEventName() {
        return event_name;
    }

    const event_data& get_event_data() const {
        return data;
    }
};

#endif //OOP_GENERIC_EVENT_H
