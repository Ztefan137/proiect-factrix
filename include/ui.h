//
// Created by stefa on 3/13/2026.
//

#ifndef OOP_UI_H
#define OOP_UI_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "ui_style.h"

class ui{
protected:
    float x,y;
    float width,height;
    float visibility;
    std::vector<ui*> sub_uis;
    std::string ui_type="ui";
    ui_style internal_ui_style;
public:
    ui();
    ui(float x,float y,float width,float height);
    virtual ~ui();
    void set_type(std::string type);
    void set_style(ui_style new_ui_style);
    void set_visibility(bool new_visibility);
    void show();
    void hide();
    void add_sub_ui(ui* new_sub_ui);
    void render(sf::RenderWindow &window) const;
    virtual void render_self(sf::RenderWindow &window) const;
    float get_x() const;
    float get_y() const;
    float get_width() const;
    float get_height() const;
    bool get_visibility() const;
};


#endif //OOP_UI_H