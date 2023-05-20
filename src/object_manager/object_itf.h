#pragma once

#include "event.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <stdio.h>

#define TYPE_ENUM(e) inline static const object_type Type = e

namespace bk
{

enum class object_type
{
    any,
    npc,
    player,
    button,
    room,
    bullet,
    enemy,
    person
};

class object_mgr;
class scene;

class object_itf
{
public:
    object_itf(scene& scene, object_type type) : m_scene(scene), m_type(type), m_is_hovered(false), m_z(0), m_active(true) { }
    virtual ~object_itf() = default;

    void  set_z(float z) { m_z = z; }
    float get_z() const { return m_z; }

    virtual void on_update(double dt) = 0;
    virtual void on_render(sf::RenderTarget& target) = 0;
    virtual void on_event(event e) = 0;

    void set_active(bool active) { m_active = active; }
    bool active() const { return m_active; }

    void set_hovered(bool is_hovered) { m_is_hovered = is_hovered; }

    object_type get_type() const { return m_type; }

    sf::Vector2f m_position;
    sf::Vector2f m_rotation;
    sf::Vector2f m_scale;

protected:
    float m_z;
    object_type m_type;
    scene& m_scene;
    bool m_is_hovered;
    bool m_active;

    friend class object_mgr;
};

}
