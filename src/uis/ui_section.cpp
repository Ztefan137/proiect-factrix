//
// Created by stefa on 3/31/2026.
//

#include "ui_section.h"

ui_section::ui_section(float x, float y, float width, float height,const std::string& section_name,bool visible_header) : ui(x,y,width,height){
    this->section_name = section_name;
    this->section_header = visible_header;
}

bool ui_section::get_header_visibility() const{
    return this->section_header;
}

void ui_section::set_header_visibility(bool visible) {
    this->section_header = visible;
}
std::string ui_section::get_section_name() const{
    return this->section_name;
}
