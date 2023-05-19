#pragma once

#include "SFML/Graphics.hpp"

namespace bk
{

class object_mgr;
class scene;

class object_itf
{
public:

    object_itf(scene& scene) : m_scene(scene) { }

    virtual void on_update() = 0;
    virtual void on_render() = 0;

protected:

    scene& m_scene;
    sf::Transform m_transform;

    friend class object_mgr;
};

}