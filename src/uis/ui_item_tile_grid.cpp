//
// Created by stefa on 4/13/2026.
//

#include "ui_item_tile_grid.h"

#include "ui_item_tile.h"

#include <iostream>

ui_item_tile_grid::ui_item_tile_grid(float x, float y, float width, float height,int cols,int rows,float tile_size, item* reference) : ui(x,y,width,height){
    this->cols = cols;
    this->rows = rows;
    this->tile_size = tile_size;
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            ui* grid_tile=new ui_item_tile(x-3*120+j*120,y-4*110+i*110,tile_size,tile_size,reference);
            grid_tile->set_type("item_tile");
            if (reference != nullptr) {
                reference++;
            }
            this->add_sub_ui(grid_tile);
        }
    }
}

int ui_item_tile_grid::get_cols() {
    return this->cols;
}

int ui_item_tile_grid::get_rows() {
    return this->rows;
}

float ui_item_tile_grid::get_tile_size() {
    return this->tile_size;
}

void ui_item_tile_grid::bind_data(ui_binder *binder) {
    std::cout<<"bind data"<<std::endl;
    item* reference = binder->get<item>(this->bind_string);
    for (ui* base_ui : sub_uis) {
        ui_item_tile* tile = dynamic_cast<ui_item_tile*>(base_ui);
        if (tile && reference) {
            tile->set_item(reference);
            reference++;
        }
    }
}

void ui_item_tile_grid::set_action_string(std::string new_action_string) {
    this->action_string=new_action_string;
    for (ui* ui : sub_uis) {
        ui->set_action_string(new_action_string);
    }
}
