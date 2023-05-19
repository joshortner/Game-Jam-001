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

    // movement is 
    // a = (F - k*v) / m
    // k is -FRICTION
    // F is the 'move_dir' we're setting here.
    // we know that dv = a * dt -> dv = (F - k * v)*t / m
    // solve the differential equation to get 
    //  v(t) = Ce^{-kt/m} + F/k
    // as t -> infinity, v(infinity) = F/k = max velocity => F = max_velocity * k.
    void object_player::on_update(double dt)
    {
        float mag = m_max_vel * K;
        sf::Vector2f F = { 0, 0 };
        if (m_movement[0]) F.y -= mag;
        if (m_movement[1]) F.y += mag;
        if (m_movement[2]) F.x -= mag;
        if (m_movement[3]) F.x += mag;
        
        if (F.length()) F = F.normalized() * mag;
        
        const float m = 1.f;
        sf::Vector2f a = (F - 3.f * K * m_velocity) / m;
        m_velocity += a * (float)dt;

        rect.move(m_velocity);
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