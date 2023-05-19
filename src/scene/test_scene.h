#pragma once

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
    sf::Vector2<double> position = sf::Vector2<double>(0, 0);
    animation_system m_system;
};

}