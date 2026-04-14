//
// Created by stefa on 4/13/2026.
//

#ifndef OOP_UI_ITEM_TILE_GRID_H
#define OOP_UI_ITEM_TILE_GRID_H
#include "ui.h"
#include "item.h"
class ui_item_tile_grid : public ui{
    int cols,rows;
    float tile_size;
public:
    ui_item_tile_grid(float x,float y,float width,float height,int cols,int rows,float tile_size,item* reference);
    int get_cols();
    int get_rows();
    float get_tile_size();
    void bind_data(ui_binder *binder) override;
};


#endif //OOP_UI_ITEM_TILE_GRID_H