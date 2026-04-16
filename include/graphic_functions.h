//
// Created by stefa on 3/13/2026.
//

#ifndef OOP_GRAPHIC_FUNCTIONS_H
#define OOP_GRAPHIC_FUNCTIONS_H
#include <SFML/Graphics.hpp>
#include <string>
#include "item.h"

void rect(sf::RenderWindow& window_obj,float xi,float yi, float xf, float yf,sf::Color color);
void text(sf::RenderWindow& window_obj,float x,float y,std::string text,bool bold);
void render_item(sf::RenderWindow& window_obj,float x,float y,item* type);
#endif //OOP_GRAPHIC_FUNCTIONS_H