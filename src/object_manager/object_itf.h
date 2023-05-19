#pragma once

#include "event.h"

#include <SFML/Graphics.hpp>

namespace bk
{
enum class object_type
{
    npc,
    player,
    room
};

class object_mgr;
class scene;

class object_itf
{
public:
    object_itf(scene& scene, object_type type) : m_scene(scene), m_type(type), m_z(0) { }
    virtual ~object_itf() = default;

    void  set_z(float z) { m_z = z; }
    float get_z() const { return m_z; }

    virtual void on_update(double dt) = 0;
    virtual void on_render(sf::RenderTarget& target) = 0;
    virtual void on_event(event e) = 0;

    object_type get_type() const { return m_type; }

protected:
    float m_z;
    object_type m_type;
    scene& m_scene;
    sf::Transform m_transform;

    friend class object_mgr;
};

}