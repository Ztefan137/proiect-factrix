//
// Created by stefa on 4/6/2026.
//

#include "../../include/key_event.h"

key_event::key_event(std::string key) {
    this->key=key;
}

std::string key_event::get_key() {
    return this->key;
}
