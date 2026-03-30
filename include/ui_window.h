//
// Created by stefa on 3/30/2026.
//

#ifndef OOP_UI_WINDOW_H
#define OOP_UI_WINDOW_H
#include "ui.h"
#include <string>


class ui_window : public ui{
    std::string window_name;
public:
    ui_window(float x,float y,float width,float height,std::string window_name);
    std::string get_window_name() const;
};


#endif //OOP_UI_WINDOW_H