//
// Created by stefa on 3/13/2026.
//

#include  <../include/graphic_functions.h>
#include "item.h"

void rect(sf::RenderWindow& window_obj,float xi,float yi, float xf, float yf,sf::Color color) {
    sf::RectangleShape rect;
    rect.setPosition({xi,yi});
    rect.setSize({xf-xi,yf-yi});
    rect.setFillColor(color);
    window_obj.draw(rect);
}
void text(sf::RenderWindow& window_obj,float x,float y,std::string text,bool bold) {
    static sf::Font normal_font;
    static sf::Font bold_font;
    if (!normal_font.openFromFile("assets/fonts/TitilliumWeb-Regular.ttf")){}
    if (!bold_font.openFromFile("assets/fonts/TitilliumWeb-Bold.ttf")){}
    sf::Text text_obj(normal_font);
    if (bold) {
        text_obj.setFont(bold_font);
    }
    text_obj.setPosition({x,y});
    text_obj.setString(text);
    text_obj.setCharacterSize(34);
    text_obj.setFillColor(sf::Color::White);
    window_obj.draw(text_obj);
}

void render_item(sf::RenderWindow &window_obj, float x, float y, item* item) {
    static std::unordered_map<std::string, sf::Texture> icons;
    static bool initialized = false;
    static std::optional<sf::Sprite> sprite;
    if (!initialized) {
        icons["iron_ore"].loadFromFile("assets/icons/iron_ore.png");
        icons["furnace"].loadFromFile("assets/buildings/furnace.png");
        initialized = true;
    }
    auto it = icons.find(item->get_name());
    if (it == icons.end()) {
        return;
    }
    sf::Texture* tex = &it->second;
    if (!sprite.has_value()) {
        sprite.emplace(*tex);
    } else {
        sprite->setTexture(*tex, true);
    }

    sprite->setPosition({x + 10, y + 10});

    float target = 80.f;
    sf::Vector2u s = tex->getSize();
    float scale = target / std::max(s.x, s.y);
    sprite->setScale({scale, scale});

    window_obj.draw(*sprite);

    if (item->get_quantity() > 1) {
        text(window_obj, x + 55, y + 55, std::to_string(item->get_quantity()), true);
    }
}