//
// Created by stefa on 3/13/2026.
//

#include  <../include/graphic_functions.h>

void rect(sf::RenderWindow& window_obj,float xi,float yi, float xf, float yf,sf::Color color) {
    sf::RectangleShape rect;
    rect.setPosition({xi,yi});
    rect.setSize({xf-xi,yf-yi});
    rect.setFillColor(color);
    window_obj.draw(rect);
}
void text(sf::RenderWindow& window_obj,float x,float y,std::string text) {
    sf::Font font;
    if (!font.openFromFile("assets/fonts/TitilliumWeb-Regular.ttf")){}
    sf::Text text_obj(font);
    text_obj.setPosition({x,y});
    text_obj.setString(text);
    text_obj.setCharacterSize(34);
    text_obj.setFillColor(sf::Color::White);
    window_obj.draw(text_obj);
}