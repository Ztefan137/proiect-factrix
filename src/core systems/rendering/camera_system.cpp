//
// Created by stefa on 4/27/2026.
//

#include "../../../include/camera_system.h"

#include "generic_event.h"
#include "structures.h"

camera_system::camera_system(sf::RenderWindow &window) : window(window){
}

float camera_system::get_zoom() const{
    return this->zoom_level;
}

float camera_system::get_camera_x() const{
    return this->x_camera;
}

float camera_system::get_camera_y() const{
    return this->y_camera;
}

float camera_system::get_tile_size() const{
    return this->tile_size;
}

void camera_system::init_camera() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    const unsigned int screenWidth = desktop.size.x;
    const unsigned int screenHeight = desktop.size.y;

    sf::Vector2u windowSize = window.getSize();
    float aspectRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
    float worldHeight = windowSize.y;
    float worldWidth  = worldHeight * aspectRatio;
    this->camera=sf::View(sf::FloatRect({0.f, 0.f}, {worldWidth, worldHeight}));

    constexpr bool high_resolution=true;

    const float ui_width  = high_resolution?2880.f:1920.f;
    const float ui_height = high_resolution?1800.f:1080.f;

    this->ui_camera=sf::View(sf::FloatRect({0.f, 0.f}, {ui_width, ui_height}));
    this->ui_camera.setViewport(sf::FloatRect({0.f, 0.f}, {1.f, 1.f}));
    this->ui_camera.setCenter({screenWidth / 2.f, screenHeight / 2.f});

    this->window.setView(camera);
    this->set_camera(x_camera,y_camera);
    this->set_zoom(zoom_level);
}

void camera_system::set_camera(float new_x_camera,float new_y_camera) {
    this->x_camera = new_x_camera;
    this->y_camera = new_y_camera;
}

void camera_system::set_zoom(float new_zoom_level) {
    this->zoom_level = new_zoom_level;
}

void camera_system::set_tile_size(float new_tile_size) {
    this->tile_size=new_tile_size;
}

void camera_system::zoom(float delta) {
    float zoomFactor = delta > 0 ? 0.9f : 1.1f;
    float newZoom = this->zoom_level * zoomFactor;
    constexpr float min_zoom = 0.7f;
    constexpr float max_zoom = 20.f;
    if (newZoom < min_zoom || newZoom > max_zoom)
        return;

    this->zoom_level = newZoom;
    this->camera.zoom(zoomFactor);
}