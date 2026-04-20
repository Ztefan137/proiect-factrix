//
// Created by stefa on 4/19/2026.
//

#ifndef OOP_UI_PROGRESS_BAR_H
#define OOP_UI_PROGRESS_BAR_H
#include "ui.h"


class ui_progress_bar : public ui{
    float progress=0.f;
    sf::Color color=sf::Color::White;
public:
    ui_progress_bar(float x,float y,float width,float height,sf::Color color);
    void reset();
    void advance_progress(float d_progress);
    float get_progress() const;
    sf::Color get_color() const;
};


#endif //OOP_UI_PROGRESS_BAR_H