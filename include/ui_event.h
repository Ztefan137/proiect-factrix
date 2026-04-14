//
// Created by stefa on 4/14/2026.
//

#ifndef OOP_UI_EVENT_H
#define OOP_UI_EVENT_H
#include "event.h"
#include "ui_binder.h"

class ui_event : public event{
    ui_binder* binder;
    int index=0;
public:
    ui_event(int index,ui_binder* binder);
    ui_binder* get_binder();
    int get_index();
};


#endif //OOP_UI_EVENT_H