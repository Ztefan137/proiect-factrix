//
// Created by stefa on 4/13/2026.
//

#ifndef OOP_UI_ITEM_TILE_H
#define OOP_UI_ITEM_TILE_H
#include "ui.h"
#include "item.h"

class ui_item_tile : public ui{
    item* internal_item=nullptr;
public:
    ui_item_tile(float x,float y,float width,float height,item* new_item=nullptr);
    void bind_data(ui_binder *binder) override;
    void set_item(item* new_item);
    item* get_item() const;
};


#endif //OOP_UI_ITEM_TILE_H