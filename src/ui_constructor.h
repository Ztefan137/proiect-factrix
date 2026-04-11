//
// Created by stefa on 4/11/2026.
//

#ifndef OOP_UI_CONSTRUCTOR_H
#define OOP_UI_CONSTRUCTOR_H
#include <string>
#include <vector>
#include "tiny-xml2/tinyxml2.h"

#include "ui.h"


class ui_constructor {
public:
    std::vector<ui*> construct_from_xml(std::string& config_xml);
    ui* construct_ui(tinyxml2::XMLElement* element);
    void construct_sub_ui_tree(ui* parent_ui, tinyxml2::XMLElement* parent);
};


#endif //OOP_UI_CONSTRUCTOR_H