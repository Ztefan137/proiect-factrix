//
// Created by stefa on 4/19/2026.
//

#ifndef OOP_MACHINE_HANDLER_H
#define OOP_MACHINE_HANDLER_H
#include <unordered_map>
#include <string>
#include <vector>

#include "belt_prototype.h"
#include "event.h"
#include "machine.h"
#include "player.h"

class machine_handler {
    std::unordered_map<std::string,machine*> machines;
    std::unordered_map<std::string,belt_prototype*> belts;
    std::vector<std::string> opened_machines;
    player* player_instance;
public:
    machine_handler(player &player);
    void add_machine(machine* machine,int x,int y);
    machine* get_machine(int x,int y);
    belt_prototype* get_belt(int x,int y);
    void delete_machine(int x,int y);
    void delete_machines();
    void open_machine(int x,int y);
    void close_machines();
    void process_event(event* event);
    void update_machines();
    friend std::ostream& operator<<(std::ostream& os,const machine_handler& handler);
    friend std::istream& operator>>(std::istream& is,machine_handler& handler);

};


#endif //OOP_MACHINE_HANDLER_H