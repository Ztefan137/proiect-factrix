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
#include <queue>
#include "event.h"
#include "action_handler.h"

class ui{
protected:
    float x,y;
    float width,height;
    bool visibility;
    std::vector<ui*> sub_uis;
    std::string ui_type="ui";
    ui_style internal_ui_style;
    std::string bind_string="";
    std::string action_string="";
    action_handler internal_action_handler;
    bool hovered=false;
public:
    ui();
    ui(float x,float y,float width,float height);
    virtual ~ui();
    void set_type(std::string type);
    void set_style(ui_style new_ui_style);
    void set_actions(action_handler new_action_handler);
    void set_visibility(bool new_visibility);
    void show();
    void hide();
    void render(sf::RenderWindow &window);
    virtual void render_self(sf::RenderWindow &window);
    float get_x() const;
    float get_y() const;
    float get_width() const;
    float get_height() const;
    bool get_visibility() const;
    bool is_mouse_inside(float x_mouse,float y_mouse);
    void check_click(float x_mouse,float y_mouse,std::queue<event*>* event_queue);
    void check_hover(float x_mouse,float y_mouse);

    void set_bind_string(std::string new_bind_string);
    virtual void set_action_string(std::string new_action_string);
    virtual void bind_data(ui_binder* binder);
    virtual void bind(ui_binder* binder);

    void add_sub_ui(ui* new_sub_ui);
};


#endif //OOP_UI_H