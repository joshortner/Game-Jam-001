#pragma once

#include "event.h"
#include "bullet_killer.h"

#include <SFML/Graphics.hpp>
#include <flecs.h>
#include <iostream>
#include <stdio.h>

//#define TYPE_ENUM(e) inline static const object_type Type = e

namespace bk
{

/*
enum class object_type
{
    any,
    npc,
    player,
    button,
    room,
    bullet,
    enemy,
    person,
    text
};*/

//class object_mgr;
//class scene;

class object_itf
{
public:
    //object_itf(scene& scene, object_type type) : m_scene(scene), m_type(type), m_is_hovered(false), m_z(0), m_active(true) { }
    virtual ~object_itf() = default;

    //void  set_z(float z) { m_z = z; }
    //float get_z() const { return m_z; }

    virtual void on_update(double dt, flecs::world& world) = 0;
    //virtual void on_render(sf::RenderTarget& target, render_pass pass) = 0;
    virtual void on_event(event e) = 0;
    //virtual sf::FloatRect get_bounding_box() const { return sf::FloatRect(m_position, m_scale); }

    //void set_active(bool active) { m_active = active; }
    //bool active() const { return m_active; }

    //double lifetime() const { return m_life.getElapsedTime().asSeconds(); }

    //void set_hovered(bool is_hovered) { m_is_hovered = is_hovered; }

    //object_type get_type() const { return m_type; }

    //sf::Vector2f m_position;
    //sf::Vector2f m_rotation;
    //sf::Vector2f m_scale;

protected:
    /*
    float m_z;
    object_type m_type;
    scene& m_scene;
    bool m_is_hovered;
    bool m_active;

    sf::Clock m_life;

    friend class object_mgr;*/
};

}
