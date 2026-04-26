//
// Created by stefa on 4/26/2026.
//

#include "ui_item_sticker_grid.h"

#include "ui_item_sticker.h"

ui_item_sticker_grid::ui_item_sticker_grid(float x, float y, float width, float height,int cols,int rows,float tile_size, item* reference) : ui(x,y,width,height){
    this->cols = cols;
    this->rows = rows;
    this->tile_size = tile_size;
    const float padding=24.f;
    width-=padding*2;
    height-=padding*2;
    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            float horizontal_gap=(width-cols*tile_size)/(cols-1);
            float vertical_gap=(height-rows*tile_size)/(rows-1);
            ui* grid_tile=new ui_item_sticker(x-(cols/2)*(horizontal_gap+tile_size)+j*(horizontal_gap+tile_size),y-(rows/2)*(vertical_gap+tile_size)+i*(vertical_gap+tile_size),tile_size,tile_size,reference);
            grid_tile->set_type("item_sticker");
            if (reference != nullptr) {
                reference++;
            }
            this->add_sub_ui(grid_tile);
        }
    }
}

int ui_item_sticker_grid::get_cols() {
    return this->cols;
}

int ui_item_sticker_grid::get_rows() {
    return this->rows;
}

float ui_item_sticker_grid::get_tile_size() {
    return this->tile_size;
}

void ui_item_sticker_grid::bind_data(ui_binder *binder) {
    //std::cout<<"bind data"<<std::endl;
    item* reference = binder->get<item>(this->bind_string);
    for (ui* base_ui : sub_uis) {
        ui_item_sticker* sticker = dynamic_cast<ui_item_sticker *>(base_ui);
        if (sticker && reference) {
            sticker->set_item(reference);
            reference++;
        }
    }
}

void ui_item_sticker_grid::set_action_string(std::string new_action_string) {
    this->action_string=new_action_string;
    for (ui* ui : sub_uis) {
        ui->set_action_string(new_action_string);
    }
}
