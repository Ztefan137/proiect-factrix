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
void craft_action(std::queue<event*>* event_queue,item* item);
void new_game(std::queue<event*>* event_queue);
void continue_game(std::queue<event*>* event_queue);
void load_game(std::queue<event*>* event_queue);
void quit_game(std::queue<event*>* event_queue);

#endif //OOP_UI_ACTIONS_H