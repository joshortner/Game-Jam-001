#pragma once

#include "scene.h"

namespace bk
{

class test_scene : 
    public bk::scene
{
public:
    using bk::scene::scene;

    virtual void on_update(double dt) override;
    virtual void on_render() override;

private:
    sf::Vector2f position = sf::Vector2f(0, 0);
};

}