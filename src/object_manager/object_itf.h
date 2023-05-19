#pragma once

#include "event.h"

#include <SFML/Graphics.hpp>

namespace bk
{

class object_mgr;
class scene;

class object_itf
{
public:

    object_itf(scene& scene) : m_scene(scene) { }

    virtual void on_update(double dt) = 0;
    virtual void on_render(const sf::RenderTarget& target) = 0;
    virtual void on_event(event e) = 0;

protected:

    scene& m_scene;
    sf::Transform m_transform;

    friend class object_mgr;
};

}