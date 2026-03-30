//
// Created by stefa on 3/30/2026.
//

#include "ui_style.h"
#include "ui.h"

void ui_style::render(const std::string &ui_type,sf::RenderWindow&window,const ui* p_ui) const {
    auto it = style_function_pointers.find(ui_type);
    if (it != style_function_pointers.end()) {
        if (it->second) {
            it->second(window,p_ui);
        } else {
        }
    }
}
void ui_style::set_function(const std::string& name,void(*func)(sf::RenderWindow&,const ui*)){
    style_function_pointers[name] = func;
}
