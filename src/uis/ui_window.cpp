//
// Created by stefa on 3/30/2026.
//

#include "ui_window.h"
#include "ui.h"
#include <string>

ui_window::ui_window(float x,float y,float width,float height,std::string window_name):ui(x,y,width,height){
    this->window_name = window_name;
}

std::string ui_window::get_window_name() const{
    return window_name;
}