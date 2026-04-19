//
// Created by stefa on 4/11/2026.
//

#include "../../../include/ui_constructor.h"
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
#include "ui_item_tile.h"
#include "ui_item_tile_grid.h"
#include "ui_section.h"

inline void position_center_padding(float x_center,float y_center,float padding_left,float padding_right,float padding_top,float padding_bottom,float &new_x_center,float &new_y_center) {
    new_x_center=x_center+0.5*(padding_left-padding_right);
    new_y_center=y_center+0.5*(padding_top-padding_bottom);
}

void ui_constructor::construct_sub_ui_tree(ui * parent_ui, tinyxml2::XMLElement* parent) {
    float flex_left_offset=0;
    int child_index=0;
    for (tinyxml2::XMLElement* child = parent->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        ui* child_ui=nullptr;
        std::string tag_name(child->Value());
        float x=parent_ui->get_x();
        float y=parent_ui->get_y();
        float width=parent_ui->get_width();
        float height=parent_ui->get_height();
        float header_height=0;
        float padding=0;
        parent->QueryFloatAttribute("padding", &padding);
        std::string parent_type(parent->Value());
        if (parent_type == "window") {
            header_height=64.f;
        }else if (parent_type == "section") {
            std::string section_ribbon_string(parent->Attribute("visible_ribbon"));
            if (section_ribbon_string == "true") {
                header_height=68.f;
            }
        }
        float paded_x=0;
        float paded_y=0;
        width-=2*padding;
        height-=(2*padding+header_height);
        position_center_padding(x,y,padding,padding,padding+header_height,padding,paded_x,paded_y);
        x=paded_x;
        y=paded_y;

        std::string parent_flex=parent->Attribute("flex");
        if (parent_flex == "true") {
            std::string flex_template=parent->Attribute("flex-template");
            std::vector<float>flex_fractions;
            for (auto fraction:st::split(flex_template,'-')) {
                flex_fractions.push_back(std::stof(fraction)/100);
            }
            float gap=0.f;
            parent->QueryFloatAttribute("flex-gap", &gap);
            float new_width=(width-static_cast<float>(flex_fractions.size()-1)*gap)*flex_fractions[child_index];
            position_center_padding(x,y,flex_left_offset,width-flex_left_offset-new_width,0,0,x,y);
            flex_left_offset+=new_width;
            flex_left_offset+=gap;
            width=new_width;
        }

        const char* bind_attr = child->Attribute("bind");
        std::string binding_string = bind_attr ? bind_attr : "";

        const char* action_attr = child->Attribute("action");
        std::string action_string = action_attr ? st::trim(action_attr) : "";

        if (tag_name == "section"){
            std::string name(child->Attribute("name"));
            std::string visible_ribbon_string(child->Attribute("visible_ribbon"));
            bool visible_ribbon=visible_ribbon_string=="true";
            child_ui=new ui_section(x,y,width,height,name,visible_ribbon); //NOLINT
            child_ui->set_type("section");
        }else if (tag_name == "button") {
            //child_ui=new ui_button(std::stof(child_ui_properties["x"]),std::stof(child_ui_properties["y"]),std::stof(child_ui_properties["width"]),std::stof(child_ui_properties["height"]),child_ui_properties["text"]);
        }else if (tag_name == "item_grid") {
            child_ui=new ui_item_tile_grid(x,y,width,height,7,7,100.f,nullptr);
            child_ui->set_type("item_tile_grid");
            child_ui->set_bind_string(binding_string);
            child_ui->set_action_string(action_string);
        }else if (tag_name == "item_tile") {
            child_ui=new ui_item_tile(x-0.5*width+flex_left_offset+80,y,100,100,nullptr);
            child_ui->set_type("item_tile");
            child_ui->set_bind_string(binding_string);
            flex_left_offset+=120;
        }
        std::cout<<"tree constructed"<<std::endl;
        if (child_ui != nullptr) {
            this->construct_sub_ui_tree(child_ui,child);
            parent_ui->add_sub_ui(child_ui);
        }
        child_index++;
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
    //window->show();
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
