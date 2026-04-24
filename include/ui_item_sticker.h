//
// Created by stefa on 4/22/2026.
//

#ifndef OOP_UI_ITEM_STICKER_H
#define OOP_UI_ITEM_STICKER_H
#include "ui.h"
#include "ui_item_element.h"


class ui_item_sticker : public ui_item_element{
    item* internal_item=nullptr;
public:
    ui_item_sticker(float x,float y,float width,float height,item* new_item=nullptr);
};


#endif //OOP_UI_ITEM_STICKER_H