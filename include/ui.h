//
// Created by stefa on 3/13/2026.
//

#ifndef OOP_UI_H
#define OOP_UI_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "ui_style.h"
#include "ui_binder.h"

class ui{
protected:
    float x,y;
    float width,height;
    bool visibility;
    std::vector<ui*> sub_uis;
    std::string ui_type="ui";
    ui_style internal_ui_style;
    std::string bind_string="";
public:
    ui();
    ui(float x,float y,float width,float height);
    virtual ~ui();
    void set_type(std::string type);
    void set_style(ui_style new_ui_style);
    void set_bind_string(std::string new_bind_string);
    void set_visibility(bool new_visibility);
    void show();
    void hide();
    void add_sub_ui(ui* new_sub_ui);
    void render(sf::RenderWindow &window) const;
    void render_self(sf::RenderWindow &window) const;
    float get_x() const;
    float get_y() const;
    float get_width() const;
    float get_height() const;
    bool get_visibility() const;
    void bind(ui_binder* binder);
    virtual void bind_data(ui_binder* binder);
};


#endif //OOP_UI_H