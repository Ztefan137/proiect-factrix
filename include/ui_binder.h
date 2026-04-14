//
// Created by stefa on 4/14/2026.
//

#ifndef OOP_UI_BINDER_H
#define OOP_UI_BINDER_H
#include <unordered_map>
#include <string>
#include <any>


class ui_binder {
    std::unordered_map<std::string, std::any> table;
public:
    template<typename T>
    void set(const std::string& key, T* value) {
        table[key] = value;
    }

    template<typename T>
    T* get(const std::string& key) {
        auto it = table.find(key);
        if (it == table.end()) return nullptr;
        return std::any_cast<T*>(it->second);
    }
};


#endif //OOP_UI_BINDER_H