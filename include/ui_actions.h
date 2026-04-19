//
// Created by stefa on 4/4/2026.
//

#ifndef OOP_UI_ACTIONS_H
#define OOP_UI_ACTIONS_H
#include "structures.h"
#include <queue>
#include "event.h"
#include <string>

#include "item.h"

void open_build_mode(std::queue<event*>* event_queue,item* item);
void furnace_item_transfer(std::queue<event*>* event_queue,item* item);
void player_item_transfer(std::queue<event*>* event_queue,item* item);

#endif //OOP_UI_ACTIONS_H