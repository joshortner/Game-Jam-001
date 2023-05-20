#include "object_player.h"

#include <iostream>

namespace bk
{
    object_player::object_player(scene& scene, const sf::Texture& bullet) :
        object_itf(scene, object_type::player),
        m_ammo(bullet)
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

        rect.move(m_velocity * (float)dt);
    }

    void object_player::on_render(sf::RenderTarget& target)
    {
        target.draw(rect);
        
        std::string bullet_string = std::to_string(bullets);

        uint32_t i = 0;
        for (const auto& c : bullet_string)
        {
            int32_t num = (c - '0') - 1;
            if (num < 0) num = 9;

            m_ammo.setPosition(rect.getPosition() + sf::Vector2f(i++ * 10, 0));
            m_ammo.setTextureRect(sf::IntRect({ 0, 16 * num }, { 16, 16 }));
            target.draw(m_ammo);
        }
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