//
// Created by stefa on 4/15/2026.
//

#include "generic_event.h"

template<typename event_data>
std::string generic_event<event_data>::getEventName() {
    return this->event_name;
}

