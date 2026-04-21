//
// Created by stefa on 3/30/2026.
//

#include "ui_render_functions.h"
#include "graphic_functions.h"
#include <cmath>

#include "ui.h"
#include "ui_window.h"
#include "ui_section.h"

#include <iostream>

#include "ui_button.h"
#include "ui_item_tile.h"
#include "ui_progress_bar.h"

/*void ui_render_style_default(sf::RenderWindow &window,const float x,const float y,const float width,const float height){
    rect(window,static_cast<float>(x - std::floor(width  / 2)),static_cast<float>(y - std::floor(height / 2)),static_cast<float>(x + std::floor(width  / 2)),static_cast<float>(y + std::floor(height / 2)),sf::Color::Black);
}
void window_render_style_1(sf::RenderWindow &window,const float x,const float y,const float width,const float height) {
    rect(window,static_cast<float>(x - std::floor(width  / 2)),static_cast<float>(y - std::floor(height / 2)),static_cast<float>(x + std::floor(width  / 2)),static_cast<float>(y + std::floor(height / 2)),sf::Color::Red);
}
void window_render_style_teststyle(sf::RenderWindow &window,const float x,const float y,const float width,const float height) {
    rect(window,static_cast<float>(x - std::floor(width  / 2)),static_cast<float>(y - std::floor(height / 2)),static_cast<float>(x + std::floor(width  / 2)),static_cast<float>(y + std::floor(height / 2)),sf::Color::Blue);
}*/
void ui_render_style_test1(sf::RenderWindow &window,const ui* ui){
    auto edge_left=static_cast<float>(ui->get_x() - std::floor(ui->get_width() / 2));
    auto edge_right=static_cast<float>(ui->get_x() + std::floor(ui->get_width()  / 2));
    auto edge_top=static_cast<float>(ui->get_y() - std::floor(ui->get_height() / 2));
    auto edge_bottom=static_cast<float>(ui->get_y() + std::floor(ui->get_height() / 2));
    rect(window,edge_left,edge_top+4,edge_right,edge_bottom,sf::Color(0x1a,0x1a,0x1a,0xaa));
    rect(window,edge_left+4,edge_top+4,edge_right-4,edge_bottom-4,sf::Color(0x3a,0x3a,0x3a,0xaa));
    rect(window,edge_left,edge_top,edge_right,edge_top+4,sf::Color(0x6a,0x6a,0x6a,0xaa));
    text(window,edge_left+40,edge_top+40,"Test ui",false);
}
void window_render_style_style1(sf::RenderWindow &window, const ui* ui)
{
    auto edge_left=static_cast<float>(ui->get_x() - std::floor(ui->get_width() / 2));
    auto edge_right=static_cast<float>(ui->get_x() + std::floor(ui->get_width()  / 2));
    auto edge_top=static_cast<float>(ui->get_y() - std::floor(ui->get_height() / 2));
    auto edge_bottom=static_cast<float>(ui->get_y() + std::floor(ui->get_height() / 2));
    rect(window, edge_left, edge_top+4, edge_right, edge_bottom, sf::Color(0x0a,0x0a,0x0a,0xaa));
    rect(window, edge_left+4, edge_top+4, edge_right-4, edge_bottom-4, sf::Color(0x2a,0x2a,0x2a,0xaa));
    rect(window, edge_left, edge_top, edge_right, edge_top+4, sf::Color(0x3a,0x3a,0x3a,0xaa));
    rect(window, edge_left, edge_top+60, edge_right, edge_top+62, sf::Color(0x1a,0x1a,0x1a,0xaa));
    text(window, edge_left + 15, edge_top + 10, dynamic_cast<const ui_window*>(ui)->get_window_name(),false);
}
void window_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui)
{
    float edge_left=(ui->get_x() - std::floor(ui->get_width() / 2));
    float edge_right=(ui->get_x() + std::floor(ui->get_width()  / 2));
    float edge_top=(ui->get_y() - std::floor(ui->get_height() / 2));
    float edge_bottom=(ui->get_y() + std::floor(ui->get_height() / 2));
    rect(window, edge_left, edge_top+4, edge_right, edge_bottom, sf::Color(0x0a,0x0a,0x0a,0xff));
    rect(window, edge_left+4, edge_top+4, edge_right-4, edge_bottom-4, sf::Color(0x2a,0x2a,0x2a,0xff));
    rect(window, edge_left, edge_top, edge_right, edge_top+4, sf::Color(0x3a,0x3a,0x3a,0xff));
    rect(window, edge_left+4, edge_top+60, edge_right-4, edge_top+64, sf::Color(0x1a,0x1a,0x1a,0xff));
    rect(window, edge_left+4, edge_top+62, edge_right-4, edge_top+64, sf::Color(0x4a,0x4a,0x4a,0xff));
    text(window, edge_left + 15, edge_top + 10, dynamic_cast<const ui_window*>(ui)->get_window_name(),true);
}
void section_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui){

    auto edge_left=static_cast<float>(ui->get_x() - std::floor(ui->get_width() / 2));
    auto edge_right=static_cast<float>(ui->get_x() + std::floor(ui->get_width()  / 2));
    auto edge_top=static_cast<float>(ui->get_y() - std::floor(ui->get_height() / 2));
    auto edge_bottom=static_cast<float>(ui->get_y() + std::floor(ui->get_height() / 2));

    rect(window,edge_left,edge_top,edge_right,edge_bottom,sf::Color(0x0a,0x0a,0x0a,0xff));
    rect(window,edge_left+4,edge_top+4,edge_right-4,edge_bottom-2,sf::Color(0x3a,0x3a,0x3a,0xff));
    rect(window,edge_left+4,edge_bottom,edge_right-4,edge_bottom-2,sf::Color(0x5a,0x5a,0x5a,0xff));
    if (dynamic_cast<const ui_section*>(ui)->get_header_visibility()){
        rect(window,edge_left+4,edge_top+4,edge_right-4,edge_top+64,sf::Color(0x1a,0x1a,0x1a,0xff));
        rect(window,edge_left+4,edge_top+64,edge_right-4,edge_top+66,sf::Color(0x0a,0x0a,0x0a,0xff));
        text(window, edge_left + 15, edge_top + 10, dynamic_cast<const ui_section*>(ui)->get_section_name(),true);
    }
}

void item_tile_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui) {
    auto edge_left=static_cast<float>(ui->get_x() - std::floor(ui->get_width() / 2));
    auto edge_right=static_cast<float>(ui->get_x() + std::floor(ui->get_width()  / 2));
    auto edge_top=static_cast<float>(ui->get_y() - std::floor(ui->get_height() / 2));
    auto edge_bottom=static_cast<float>(ui->get_y() + std::floor(ui->get_height() / 2));

    rect(window,edge_left,edge_top,edge_right,edge_bottom,sf::Color(0x1a,0x1a,0x1a,0xff));
    rect(window,edge_left+2,edge_top+2,edge_right-2,edge_bottom-2,sf::Color(0x2a,0x2a,0x2a,0xff));
    rect(window,edge_left+6,edge_top+6,edge_right-6,edge_bottom-6,sf::Color(0x2f,0x2f,0x2f,0xff));
    rect(window,edge_left+10,edge_top+10,edge_right-10,edge_bottom-10,sf::Color(0x32,0x32,0x32,0xff));
    rect(window,edge_left,edge_bottom,edge_right,edge_bottom-2,sf::Color(0x5a,0x5a,0x5a,0xff));
    render_item(window,edge_left,edge_top,dynamic_cast<const ui_item_tile*>(ui)->get_item());
}

void item_tile_render_style_style1_opaque_hover(sf::RenderWindow &window, const ui* ui) {
    auto edge_left=static_cast<float>(ui->get_x() - std::floor(ui->get_width() / 2));
    auto edge_right=static_cast<float>(ui->get_x() + std::floor(ui->get_width()  / 2));
    auto edge_top=static_cast<float>(ui->get_y() - std::floor(ui->get_height() / 2));
    auto edge_bottom=static_cast<float>(ui->get_y() + std::floor(ui->get_height() / 2));

    rect(window,edge_left,edge_top,edge_right,edge_bottom,sf::Color(0x80,0x19,0x00,0xff));
    rect(window,edge_left+2,edge_top+2,edge_right-2,edge_bottom-2,sf::Color(0xcc,0x28,0x00,0xff));
    rect(window,edge_left+6,edge_top+6,edge_right-6,edge_bottom-6,sf::Color(0xe5,0x2d,0x00,0xff));
    rect(window,edge_left+10,edge_top+10,edge_right-10,edge_bottom-10,sf::Color(0xff,0x33,0x00,0xff));
    rect(window,edge_left,edge_bottom,edge_right,edge_bottom-2,sf::Color(0xff,0x55,0x00,0xff));
    render_item(window,edge_left,edge_top,dynamic_cast<const ui_item_tile*>(ui)->get_item());
}

void item_tile_grid_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui) {
    auto edge_left=static_cast<float>(ui->get_x() - std::floor(ui->get_width() / 2));
    auto edge_right=static_cast<float>(ui->get_x() + std::floor(ui->get_width()  / 2));
    auto edge_top=static_cast<float>(ui->get_y() - std::floor(ui->get_height() / 2));
    auto edge_bottom=static_cast<float>(ui->get_y() + std::floor(ui->get_height() / 2));
    rect(window,edge_left,edge_top,edge_right,edge_bottom,sf::Color(0x00,0x00,0x00,0x00));
}

void progress_bar_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui){

    auto edge_left=static_cast<float>(ui->get_x() - std::floor(ui->get_width() / 2));
    auto edge_right=static_cast<float>(ui->get_x() + std::floor(ui->get_width()  / 2));
    auto edge_top=static_cast<float>(ui->get_y() - std::floor(ui->get_height() / 2));
    auto edge_bottom=static_cast<float>(ui->get_y() + std::floor(ui->get_height() / 2));
    auto width=static_cast<float>(ui->get_width());

    rect(window,edge_left,edge_top,edge_right,edge_bottom,sf::Color(0x0a,0x0a,0x0a,0xff));
    rect(window,edge_left+4,edge_top+4,edge_right-4,edge_bottom-2,sf::Color(0x3a,0x3a,0x3a,0xff));
    rect(window,edge_left+4,edge_bottom,edge_right-4,edge_bottom-2,sf::Color(0x5a,0x5a,0x5a,0xff));

    rect(window,edge_left+4,edge_top+4,edge_left+4+width*dynamic_cast<const ui_progress_bar*>(ui)->get_progress(),edge_bottom-4,dynamic_cast<const ui_progress_bar*>(ui)->get_color());
}

void button_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui)
{
    float edge_left=(ui->get_x() - std::floor(ui->get_width() / 2));
    float edge_right=(ui->get_x() + std::floor(ui->get_width()  / 2));
    float edge_top=(ui->get_y() - std::floor(ui->get_height() / 2));
    float edge_bottom=(ui->get_y() + std::floor(ui->get_height() / 2));

    rect(window, edge_left, edge_top+4, edge_right, edge_bottom, sf::Color(0x7a,0x7a,0x7a,0xff));
    rect(window, edge_left+4, edge_top+4, edge_right-4, edge_bottom-4, sf::Color(0x9a,0x9a,0x9a,0xff));
    rect(window, edge_left, edge_top, edge_right, edge_top+4, sf::Color(0xba,0xba,0xba,0xff));
    center_text(window,ui->get_x(),ui->get_y(),dynamic_cast<const ui_button*>(ui)->get_string(),false);
}

void button_render_style_style1_opaque_hover(sf::RenderWindow &window, const ui* ui)
{
    float edge_left=(ui->get_x() - std::floor(ui->get_width() / 2));
    float edge_right=(ui->get_x() + std::floor(ui->get_width()  / 2));
    float edge_top=(ui->get_y() - std::floor(ui->get_height() / 2));
    float edge_bottom=(ui->get_y() + std::floor(ui->get_height() / 2));

    //rect(window, edge_left, edge_top+4, edge_right, edge_bottom, sf::Color(0x7a,0x7a,0x7a,0xff));
    rect(window, edge_left+4, edge_top+4, edge_right-4, edge_bottom-4, sf::Color(0xff,0x33,0x00,0xff));
    //rect(window, edge_left, edge_top, edge_right, edge_top+4, sf::Color(0xba,0xba,0xba,0xff));
    center_text(window,ui->get_x(),ui->get_y(),dynamic_cast<const ui_button*>(ui)->get_string(),false);
}

