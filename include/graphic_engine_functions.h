//
// Created by stefa on 3/14/2026.
//
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../include/world_generator.h"
#include <map>
#include <../include/chunk.h>

#ifndef OOP_GRAPHIC_ENGINE_FUNCTIONS_H
#define OOP_GRAPHIC_ENGINE_FUNCTIONS_H

void set_scale(std::vector<sf::Texture>& textures,std::vector<sf::Sprite>& sprites,float scale);
void load_textures(std::vector <std::string> paths,std::vector <sf::Texture>& textures);
void load_images(std::vector <std::string> paths,std::vector <sf::Texture>& textures,std::vector<sf::Sprite>& sprites);
void draw_chunks(sf::RenderWindow& window_obj,float x_camera,float y_camera,float scale_factor,world_generator& world_generator,sf::Texture& texture,std::map<std::string, chunk>& chunk_cache);
void get_chunk_coords(sf::RenderWindow& window_obj,int i,int j,float tile_size,int chunk_size,float x_camera,float y_camera,int &x,int &y);
void draw_character(sf::RenderWindow& window_obj);
#endif //OOP_GRAPHIC_ENGINE_FUNCTIONS_H]
