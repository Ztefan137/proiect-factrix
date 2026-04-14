//
// Created by stefa on 4/14/2026.
//

#include "../../include/ui_event.h"

ui_event::ui_event(int index,ui_binder *binder) {
    this->index=index;
    this->binder = binder;
}

ui_binder *ui_event::get_binder() {
    return this->binder;
}

int ui_event::get_index() {
    return this->index;
}
