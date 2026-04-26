//
// Created by stefa on 4/26/2026.
//

#ifndef OOP_UI_ITEM_STICKER_GRID_H
#define OOP_UI_ITEM_STICKER_GRID_H
#include "ui_binder.h"
#include "ui.h"


class ui_item_sticker_grid : public ui{
    int cols,rows;
    float tile_size;
public:
    ui_item_sticker_grid(float x,float y,float width,float height,int cols,int rows,float tile_size,item* reference);
    int get_cols();
    int get_rows();
    float get_tile_size();
    void bind_data(ui_binder *binder) override;
    void set_action_string(std::string new_action_string) override;
};


#endif //OOP_UI_ITEM_STICKER_GRID_H