//
// Created by stefa on 4/22/2026.
//

#ifndef OOP_UI_ITEM_ELEMENT_H
#define OOP_UI_ITEM_ELEMENT_H
#include "ui.h"


class ui_item_element : public ui{
protected:
    item* internal_item=nullptr;
public:
    ui_item_element(float x,float y,float width,float height,item* new_item=nullptr);
    void bind_data(ui_binder *binder) override;
    void set_item(item* new_item);
    item* get_item() const;
};


#endif //OOP_UI_ITEM_ELEMENT_H