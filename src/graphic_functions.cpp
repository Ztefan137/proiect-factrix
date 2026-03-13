//
// Created by stefa on 3/13/2026.
//

#include  <graphic_functions.h>

void rect(sf::RenderWindow& window_obj,float xi,float yi, float xf, float yf,sf::Color color) {
    sf::RectangleShape rect;
    rect.setPosition({xi,yi});
    rect.setSize({xf-xi,yf-yi});
    rect.setFillColor(color);
    window_obj.draw(rect);
}