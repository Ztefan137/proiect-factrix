//
// Created by stefa on 3/30/2026.
//

#include "ui_render_functions.h"
#include "graphic_functions.h"
#include <cmath>

#include "ui.h"
#include "ui_window.h"

#include <iostream>

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
    text(window,edge_left+40,edge_top+40,"Test ui");
}
void window_render_style_style1(sf::RenderWindow &window, const ui* ui)
{
    auto edge_left=static_cast<float>(ui->get_x() - std::floor(ui->get_width() / 2));
    auto edge_right=static_cast<float>(ui->get_x() + std::floor(ui->get_width()  / 2));
    auto edge_top=static_cast<float>(ui->get_y() - std::floor(ui->get_height() / 2));
    auto edge_bottom=static_cast<float>(ui->get_y() + std::floor(ui->get_height() / 2));
    rect(window, edge_left, edge_top+4, edge_right, edge_bottom, sf::Color(0x1a,0x1a,0x1a,0xaa));
    rect(window, edge_left+4, edge_top+4, edge_right-4, edge_bottom-4, sf::Color(0x3a,0x3a,0x3a,0xaa));
    rect(window, edge_left, edge_top, edge_right, edge_top+4, sf::Color(0x6a,0x6a,0x6a,0xaa));
    rect(window, edge_left, edge_top+60, edge_right, edge_top+62, sf::Color(0x1a,0x1a,0x1a,0xaa));
    text(window, edge_left + 15, edge_top + 10, dynamic_cast<const ui_window*>(ui)->get_window_name());
}
void window_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui)
{
    auto edge_left=static_cast<float>(ui->get_x() - std::floor(ui->get_width() / 2));
    auto edge_right=static_cast<float>(ui->get_x() + std::floor(ui->get_width()  / 2));
    auto edge_top=static_cast<float>(ui->get_y() - std::floor(ui->get_height() / 2));
    auto edge_bottom=static_cast<float>(ui->get_y() + std::floor(ui->get_height() / 2));
    rect(window, edge_left, edge_top+4, edge_right, edge_bottom, sf::Color(0x1a,0x1a,0x1a,0xff));
    rect(window, edge_left+4, edge_top+4, edge_right-4, edge_bottom-4, sf::Color(0x3a,0x3a,0x3a,0xff));
    rect(window, edge_left, edge_top, edge_right, edge_top+4, sf::Color(0x6a,0x6a,0x6a,0xff));
    rect(window, edge_left, edge_top+60, edge_right, edge_top+62, sf::Color(0x1a,0x1a,0x1a,0xff));
    rect(window, edge_left, edge_top+60, edge_right, edge_top+61, sf::Color(0x6a,0x6a,0x6a,0xff));
    text(window, edge_left + 15, edge_top + 10, dynamic_cast<const ui_window*>(ui)->get_window_name());
}