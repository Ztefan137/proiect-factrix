//
// Created by stefa on 3/30/2026.
//
#include <SFML/Graphics.hpp>
#include "ui.h"

#ifndef OOP_UI_RENDER_FUNCTIONS_H
#define OOP_UI_RENDER_FUNCTIONS_H

//naming convention void

//void ui_render_style_default(sf::RenderWindow &window,const float x,const float y,const float width,const float height);
//void window_render_style_1(sf::RenderWindow &window,const float x,const float y,const float width,const float height);
//void window_render_style_teststyle(sf::RenderWindow &window,const float x,const float y,const float width,const float height);
void ui_render_style_test1(sf::RenderWindow &window,const ui* ui);
void window_render_style_style1(sf::RenderWindow &window,const ui* ui);
void window_render_style_style1_opaque(sf::RenderWindow &window,const ui* ui);
void section_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui);
void item_tile_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui);
void item_tile_render_style_style1_opaque_hover(sf::RenderWindow &window, const ui* ui);
void item_tile_grid_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui);
void progress_bar_render_style_style1_opaque(sf::RenderWindow &window, const ui* ui);
void button_render_style_style1_opaque(sf::RenderWindow &window,const ui* ui);
void button_render_style_style1_opaque_hover(sf::RenderWindow &window,const ui* ui);
void item_sticker_style_style1_opaque(sf::RenderWindow &window, const ui* ui);
#endif //OOP_UI_RENDER_FUNCTIONS_H