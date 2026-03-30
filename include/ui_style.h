//
// Created by stefa on 3/30/2026.
//

#ifndef OOP_UI_STYLE_H
#define OOP_UI_STYLE_H
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>

class ui;

class ui_style {
    std::unordered_map<std::string,void(*)(sf::RenderWindow&,const ui*)> style_function_pointers;
public:
    void render(const std::string &ui_type,sf::RenderWindow&window,const ui* ui) const;
    void set_function(const std::string& name,void(*func)(sf::RenderWindow&,const ui*));
};


#endif //OOP_UI_STYLE_H