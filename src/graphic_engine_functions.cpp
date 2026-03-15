//
// Created by stefa on 3/14/2026.
//

#include <iostream>

#include <SFML/Graphics.hpp>
#include "graphic_engine_functions.h"
#include <vector>
#include <cmath>
#include "chunk.h"
#include <map>

struct chunk_position {
    int i,j;
};

//unused
void set_scale(std::vector<sf::Texture>& textures,std::vector<sf::Sprite>& sprites,float scale){
    for (int i = 0;i<sprites.size();i++) {
        const float targetWidth = scale;
        const float targetHeight = scale;
        sf::Vector2u texSize = textures[i].getSize();
        float scaleX = targetWidth / texSize.x;
        float scaleY = targetHeight / texSize.y;
        sprites[i].setScale({scaleX, scaleY});
    }
}

//unused
void load_textures(std::vector<std::string> paths, std::vector<sf::Texture> &textures) {
    textures.clear();
    for (int i=0;i<paths.size();i++) {
        sf::Texture texture;
        if (!texture.loadFromFile(paths[i])) {
            continue;
        }
        textures.push_back(texture);
    }
}

//unused
void load_images(std::vector <std::string> paths,std::vector <sf::Texture>& textures,std::vector<sf::Sprite>& sprites){
    sprites.clear();
    load_textures(paths,textures);
    for (int i = 0;i<paths.size();i++) {
        sf::Sprite sprite(textures[i]);
        const float targetWidth = 150.f;
        const float targetHeight = 150.f;
        sf::Vector2u texSize = textures[i].getSize();
        float scaleX = targetWidth / texSize.x;
        float scaleY = targetHeight / texSize.y;
        sprite.setScale({scaleX, scaleY});
        sprites.push_back(sprite);
    }
}

void get_visible_chunks(float x_camera,float y_camera,float scale_factor,std::vector<chunk_position>& visible_chunks){
    const int x_camera_floored=floor(x_camera);
    const int y_camera_floored=floor(y_camera);
    const int chunk_j=x_camera_floored/32;
    const int chunk_i=y_camera_floored/32;
    const int di[8]={-1,-1,0,1,1,1,0,-1};
    const int dj[8]={0,1,1,1,0,-1,-1,-1};
    visible_chunks.push_back({chunk_i,chunk_j});
    for (int i=0;i<8;i++) {
        visible_chunks.push_back({chunk_i+di[i],chunk_j+dj[i]});
    }
}
void get_chunk_coords(sf::RenderWindow& window,int chunk_i,int chunk_j,float tile_size,int chunk_size,float x_camera,float y_camera,float &x,float &y){

    const int tile_col_count = (int)(window.getSize().x / tile_size);
    const int tile_row_count = (int)(window.getSize().y / tile_size);

    const int center_x = tile_col_count / 2;
    const int center_y = tile_row_count / 2;

    const int camera_chunk_j = (int)(std::floor(x_camera / chunk_size));
    const int camera_chunk_i = (int)(std::floor(y_camera / chunk_size));

    float local_x = std::fmod(x_camera, (float)(chunk_size));
    float local_y = std::fmod(y_camera, (float)(chunk_size));

    if (local_x < 0) local_x += chunk_size;
    if (local_y < 0) local_y += chunk_size;

    const int delta_x = chunk_j - camera_chunk_j;
    const int delta_y = chunk_i - camera_chunk_i;

    const float chunk_pixel_size = tile_size * chunk_size;

    x = (center_x - local_x) * tile_size + delta_x * chunk_pixel_size;
    y = (center_y - local_y) * tile_size + delta_y * chunk_pixel_size;
}
void draw_chunks(sf::RenderWindow& window_obj,float x_camera,float y_camera,float scale_factor,world_generator& world_generator,sf::Texture& texture,std::map<std::string, chunk>& chunk_cache) {
    std::vector<chunk_position> visible_chunks;
    get_visible_chunks(x_camera,y_camera,scale_factor,visible_chunks);

    for (int i=0;i<visible_chunks.size();i++) {
        const std::string cache_key=std::to_string(visible_chunks[i].i) + "," + std::to_string(visible_chunks[i].j);
        auto it = chunk_cache.find(cache_key);
        if (it != chunk_cache.end()) {
            chunk *rendered_chunk = &it->second;
            float chunk_x=0;
            float chunk_y=0;
            get_chunk_coords(window_obj,visible_chunks[i].i,visible_chunks[i].j,32,32,x_camera,y_camera,chunk_x,chunk_y);
            rendered_chunk->render(window_obj,chunk_x,chunk_y,32,texture);
        } else {
            chunk rendered_chunk(visible_chunks[i].i,visible_chunks[i].j,world_generator,true);
            rendered_chunk.compute_va();
            chunk_cache[cache_key]=rendered_chunk;
        }
    }
}

void draw_character(sf::RenderWindow &window_obj) {
}
