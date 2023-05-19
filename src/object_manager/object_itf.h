#pragma once

#include "event.h"

#include <SFML/Graphics.hpp>

namespace bk
{
enum class object_type
{
    npc,
    player
};

class object_mgr;
class scene;

class object_itf
{
public:
    object_itf(scene& scene, object_type type) : m_scene(scene), m_type(type) { }

    virtual void on_update(double dt) = 0;
    virtual void on_render(sf::RenderTarget& target) = 0;
    virtual void on_event(event e) = 0;

    object_type get_type() const { return m_type; }

protected:
    object_type m_type;
    scene& m_scene;
    sf::Transform m_transform;

    friend class object_mgr;
};

}