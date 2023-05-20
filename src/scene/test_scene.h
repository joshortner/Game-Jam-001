#pragma once

#include "../object_manager/object_player.h"
#include "../animation/animation_system.h"
#include "../systems/bullet_system.h"
#include "../systems/room_system.h"
#include "scene.h"

namespace bk
{

class test_scene : 
    public bk::scene
{
public:
    test_scene(const sf::Vector2u& dimensions);

    void on_update(double dt) override;
    void on_render() override;
    void on_event(event event) override;

private:
    sf::Texture m_ammo_texture;

    bullet_system m_bullet_system;
    room_system   m_room_system;

    object_player* m_player;
    sf::Vector2<double> target_pos;
    sf::Vector2<double> camera_pos;
};

}