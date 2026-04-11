//
// Created by stefa on 4/11/2026.
//

#include "../include/ui_constructor.h"
#include <vector>
#include "ui.h"
#include "ui_window.h"
#include <fstream>
#include <string>
#include <iostream>
#include "tiny-xml2/tinyxml2.h"
#include <map>
#include "string_functions.h"
#include "ui_button.h"
#include "ui_section.h"

void ui_constructor::construct_sub_ui_tree(ui * parent_ui, tinyxml2::XMLElement* parent) {
    for (tinyxml2::XMLElement* child = parent->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        ui* child_ui=nullptr;
        std::string tag_name(child->Value());

        std::map<std::string, std::string> parent_ui_properties;
        for (const tinyxml2::XMLAttribute* attr = parent->FirstAttribute(); attr != nullptr; attr = attr->Next()) {
            std::string name(attr->Name());
            std::string value(attr->Value());
            std::cout<<st::trim(name)<<": "<<st::trim(value)<<std::endl;
            parent_ui_properties[name]=value;
        }

        std::map<std::string, std::string> child_ui_properties;
        for (const tinyxml2::XMLAttribute* attr = child->FirstAttribute(); attr != nullptr; attr = attr->Next()) {
            std::string name(attr->Name());
            std::string value(attr->Value());
            std::cout<<st::trim(name)<<": "<<st::trim(value)<<std::endl;
            child_ui_properties[name]=value;
        }
        float header_height=66.f;
        if (parent->Attribute("padding")) {
            float padding=std::stof(parent_ui_properties["padding"]);
            child_ui_properties["x"]=parent_ui_properties["x"];
            child_ui_properties["y"]=std::to_string(std::stof(parent_ui_properties["y"])+0.5*(header_height));
            child_ui_properties["width"]=std::to_string(std::stof(parent_ui_properties["width"])-2*padding);
            child_ui_properties["height"]=std::to_string(std::stof(parent_ui_properties["height"])-header_height-2*padding);
        }else {
            child_ui_properties["x"]=parent_ui_properties["x"];
            child_ui_properties["y"]=std::to_string(std::stof(parent_ui_properties["y"])+33.f);
            child_ui_properties["width"]=parent_ui_properties["width"];
            child_ui_properties["height"]=std::to_string(std::stof(parent_ui_properties["height"])-66.f);;
        }
        if (tag_name == "section"){
            child_ui=new ui_section(std::stof(child_ui_properties["x"]),std::stof(child_ui_properties["y"]),std::stof(child_ui_properties["width"]),std::stof(child_ui_properties["height"]),child_ui_properties["name"],(child_ui_properties["visible_ribbon"]=="true")?true:false); //NOLINT
            child_ui->set_type("section");
        }else if (tag_name == "button") {
            //child_ui=new ui_button(std::stof(child_ui_properties["x"]),std::stof(child_ui_properties["y"]),std::stof(child_ui_properties["width"]),std::stof(child_ui_properties["height"]),child_ui_properties["text"]);
        }else if (tag_name == "item_grid") {
            //child_ui=new ui_button(std::stof(child_ui_properties["x"]),std::stof(child_ui_properties["y"]),std::stof(child_ui_properties["width"]),std::stof(child_ui_properties["height"]),child_ui_properties["text"]);
        }
        std::cout<<"tree constructed"<<std::endl;
        //this->construct_sub_ui_tree(child_ui,child);
        parent_ui->add_sub_ui(child_ui);
    }
}

ui *ui_constructor::construct_ui(tinyxml2::XMLElement* element) {
    std::map<std::string, std::string> ui_properties;
    for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr != nullptr; attr = attr->Next()) {
        std::string name(attr->Name());
        std::string value(attr->Value());
        std::cout<<st::trim(name)<<": "<<st::trim(value)<<std::endl;
        ui_properties[name]=value;
    }
    ui* window=new ui_window(std::stof(ui_properties["x"]),std::stof(ui_properties["y"]),std::stof(ui_properties["width"]),std::stof(ui_properties["height"]),ui_properties["name"]); // NOLINT
    this->construct_sub_ui_tree(window,element);
    window->show();
    window->set_type("window");
    return window;
}

std::vector<ui *> ui_constructor::construct_from_xml(std::string &config_xml) {
    std::vector<ui *> uis;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError err=doc.LoadFile(config_xml.c_str());
    if (err) {}
    tinyxml2::XMLElement* pRoot = doc.FirstChildElement("ui_list");
    tinyxml2::XMLElement* curr_ui=pRoot->FirstChildElement();
    std::string ui_count_text(pRoot->Attribute("length"));
    for (int i=0;i<std::stoi(ui_count_text);i++) {
        std::cout<<"ui:"<<i+1<<"/"<<ui_count_text<<std::endl;
        uis.push_back(this->construct_ui(curr_ui));
        curr_ui=curr_ui->NextSiblingElement();
    }
    return uis; // NOLINT
}
