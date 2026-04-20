//
// Created by stefa on 4/4/2026.
//
#ifndef OOP_UI_BUTTON_H
#define OOP_UI_BUTTON_H

#include "ui.h"
#include <string>

class ui_button : public ui {
    std::string text;

public:
    ui_button(float x,float y,float width,float height,std::string text);
    std::string get_string() const;
};

#endif //OOP_UI_BUTTON_H