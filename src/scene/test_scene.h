#pragma once

#include "../object_manager/object_player.h"
#include "../animation/animation_system.h"
#include "scene.h"

namespace bk
{

class test_scene : 
    public bk::scene
{
public:
    test_scene(const sf::Vector2u& dimensions);

    virtual void on_update(double dt) override;
    virtual void on_render() override;

private:
    object_player* m_player;
    sf::Vector2<double> target_pos;
    sf::Vector2<double> camera_pos;
};

}