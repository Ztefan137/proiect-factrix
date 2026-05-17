//
// Created by stefa on 4/27/2026.
//

#ifndef OOP_CAMERA_SYSTEM_H
#define OOP_CAMERA_SYSTEM_H
#include <SFML/Graphics.hpp>

class camera_system {
    //trebuia sa faca parte dintr un refactor al graphic_engine

    sf::View camera;
    sf::View ui_camera;
    sf::RenderWindow& window;
    float x_camera;
    float y_camera;
    float zoom_level;
    float tile_size=64;
public:
    camera_system(sf::RenderWindow& window);
    void init_camera();
    void set_camera(float x_camera,float y_camera);
    void set_zoom(float zoom_level);
    float get_zoom() const;
    float get_camera_x() const;
    float get_camera_y() const;
    void zoom(float delta);
    float get_tile_size() const;
    void set_tile_size(float new_tile_size);
};


#endif //OOP_CAMERA_SYSTEM_H