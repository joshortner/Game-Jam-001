#include "object_player.h"

#include <iostream>

namespace bk
{
    object_player::object_player(scene& scene) :
        object_itf(scene, object_type::player)
    {
        rect.setFillColor(sf::Color::Red);
        rect.setSize({ 16.f, 16.f });
        rect.setOrigin({ rect.getSize().x / 2.f, rect.getSize().y / 2.f });
    }

    void object_player::on_update(double dt)
    {
        float mag = 1.f;
        move_dir = { 0, 0 };
        if (m_movement[0]) move_dir.y -= mag;
        if (m_movement[1]) move_dir.y += mag;
        if (m_movement[2]) move_dir.x -= mag;
        if (m_movement[3]) move_dir.x += mag;
        
        const float length = move_dir.length();
        if (length) move_dir = move_dir.normalized() * mag;
        rect.move(move_dir);
    }

    void object_player::on_render(sf::RenderTarget& target)
    {
        target.draw(rect);
    }

    void object_player::on_event(event e)
    {
        if (e.m_type == event_type::key_press)
        {
            switch (e.m_key.code)
            {
            case sf::Keyboard::W: m_movement[0] = 1; break;
            case sf::Keyboard::S: m_movement[1] = 1; break;
            case sf::Keyboard::A: m_movement[2] = 1; break;
            case sf::Keyboard::D: m_movement[3] = 1; break;
            }
        }
        else if (e.m_type == event_type::key_release)
        {
            switch (e.m_key.code)
            {
            case sf::Keyboard::W: m_movement[0] = 0; break;
            case sf::Keyboard::S: m_movement[1] = 0; break;
            case sf::Keyboard::A: m_movement[2] = 0; break;
            case sf::Keyboard::D: m_movement[3] = 0; break;
            }
        }
    }
}