//
// Created by stefa on 3/31/2026.
//

#ifndef OOP_UI_SECTION_H
#define OOP_UI_SECTION_H
#include "ui.h"
#include <string>

class ui_section : public ui{
    std::string section_name;
    bool section_header=false;
public:
    ui_section(float x,float y,float width,float height,const std::string& window_name,bool visible_header);
    bool get_header_visibility() const;
    void set_header_visibility(bool visible);
    std::string get_section_name() const;
};


#endif //OOP_UI_SECTION_H