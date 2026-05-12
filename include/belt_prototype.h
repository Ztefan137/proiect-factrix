//
// Created by stefa on 5/10/2026.
//

#ifndef OOP_BELT_PROTOTYPE_H
#define OOP_BELT_PROTOTYPE_H
#include <machine.h>

#include "item.h"

class belt_prototype : public machine{
    item curr_item;
    item cached_item;
public:
    belt_prototype();
    void update() override;
    void cache_items();
    void move_items(belt_prototype*,belt_prototype*,belt_prototype*);
    item get_cached();
    void place_item(item);
};


#endif //OOP_BELT_PROTOTYPE_H