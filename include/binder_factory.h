//
// Created by stefa on 5/17/2026.
//

#ifndef OOP_BINDER_FACTORY_H
#define OOP_BINDER_FACTORY_H
#include "ui_binder.h"
#include "game_session.h"

class binder_factory {
public:
    binder_factory();
    static bool create_binder(ui_binder&,std::string type,game_session& session);
    static bool create_binder(ui_binder&,std::string type,game_session& session,int tile_x,int tile_y);
};


#endif //OOP_BINDER_FACTORY_H