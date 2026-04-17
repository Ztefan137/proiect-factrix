//
// Created by stefa on 3/13/2026.
//

#include  <../include/graphic_functions.h>
#include "item.h"
#include <map>

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
    }else{
        sprite->setTexture(*tex, true);
    }
    sprite->setPosition({x + 10, y + 10});
    float target = 80.f;
    sf::Vector2u s = tex->getSize();
    float scale = target / std::max(s.x, s.y);
    sprite->setScale({scale, scale});
    window_obj.draw(*sprite);
    if (item->get_quantity() > 1) {
        text(window_obj, x + ((item->get_quantity() == 100 )? 40:58), y + 55, std::to_string(item->get_quantity()), true);
    }
}
void render_image(sf::RenderWindow& window_obj, float x, float y, float width, float height, std::string image_path) {
    static std::map<std::string, sf::Texture> texture_cache;

    auto it = texture_cache.find(image_path);
    if (it == texture_cache.end()) {
        sf::Texture new_texture;
        if (!new_texture.loadFromFile(image_path)) {
            return;
        }
        it = texture_cache.emplace(image_path, std::move(new_texture)).first;
    }

    sf::Sprite sprite(it->second);
    sprite.setPosition({x - width, y - height});

    sf::Vector2u texture_size = it->second.getSize();
    if (texture_size.x != 0 && texture_size.y != 0) {
        sprite.setScale({width / static_cast<float>(texture_size.x), height / static_cast<float>(texture_size.y)});
    }

    window_obj.draw(sprite);
}

void draw_selector(sf::RenderWindow& window, float x, float y, float size, float scale, sf::Color color) {
    float ax = x - size;
    float ay = y - size;
    float thickness = size * 0.08f * scale;
    float length = size * 0.25f;
    float s1 = thickness * 0.2f;
    float s2 = thickness * 0.5f;
    float s3 = thickness * 0.8f;

    auto draw_brackets = [&](sf::Color c, float ox, float oy) {
        auto corner = [&](float left, float top, float right, float bottom, bool isRight, bool isBottom) {
            float cx = isRight ? right : left;
            float cy = isBottom ? bottom : top;
            float dx = isRight ? -1.0f : 1.0f;
            float dy = isBottom ? -1.0f : 1.0f;

            auto safe_rect = [&](float x1, float y1, float x2, float y2) {
                float rx1 = x1 + ox + ax;
                float ry1 = y1 + oy + ay;
                float rx2 = x2 + ox + ax;
                float ry2 = y2 + oy + ay;
                rect(window, std::min(rx1, rx2), std::min(ry1, ry2), std::max(rx1, rx2), std::max(ry1, ry2), c);
            };

            safe_rect(cx + dx * s3, cy, cx + dx * length, cy + dy * thickness);
            safe_rect(cx, cy + dy * s3, cx + dx * thickness, cy + dy * length);
            safe_rect(cx + dx * s2, cy + dy * s1, cx + dx * s3, cy + dy * thickness);
            safe_rect(cx + dx * s1, cy + dy * s2, cx + dx * thickness, cy + dy * s3);
            safe_rect(cx + dx * thickness, cy + dy * thickness, cx + dx * s3, cy + dy * s2);
            safe_rect(cx + dx * s3, cy + dy * s3, cx + dx * s2, cy + dy * thickness);
        };

        corner(0, 0, size, size, false, false);
        corner(0, 0, size, size, true, false);
        corner(0, 0, size, size, false, true);
        corner(0, 0, size, size, true, true);
    };

    draw_brackets(sf::Color(0, 0, 0, 60), 3.0f, 3.0f);
    draw_brackets(sf::Color(0, 0, 0, 40), 1.5f, 1.5f);
    draw_brackets(color, 0.0f, 0.0f);
}