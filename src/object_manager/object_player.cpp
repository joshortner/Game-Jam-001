#include "object_player.h"

#include "object_bullet.h"
#include "../scene/scene.h"

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
        set_z(-400);
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

        std::vector<object_bullet*> bullets;
        m_scene.get_game_state().m_obj_mgr.get_object_type(bullets);
        for (auto* bullet : bullets)
        {
            if (rect.getGlobalBounds().contains(bullet->get_pos()) && !bullet->get_player_owned())
            {
                m_scene.get_game_state().m_obj_mgr.remove_object(bullet);
                hp -= 0.05;
            }
        }
    }

    void object_player::on_render(sf::RenderTarget& target, render_pass pass)
    {
        switch (pass)
        {
            case render_pass::draw: draw_pass(target); break;
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
            case sf::Keyboard::R: bullets = 100; break;
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

    void object_player::draw_pass(sf::RenderTarget& target)
    {
        target.draw(rect);

        sf::RectangleShape health_bar;
        health_bar.setFillColor(sf::Color::Red);
        health_bar.setSize(sf::Vector2f(16 * 10, 16));
        health_bar.setOrigin(sf::Vector2f(
            0,
            health_bar.getSize().y / 2.f
        ));
        health_bar.setPosition(m_scene.get_view().getCenter() - (sf::Vector2f)target.getSize() / 2.f);
        health_bar.move(sf::Vector2f(
            (float)target.getSize().x / 2.f - health_bar.getSize().x / 2.f,
            (float)target.getSize().y - 13
        ));
        health_bar.setOutlineThickness(2.f);
        health_bar.setOutlineColor(sf::Color::Black);
        target.draw(health_bar);

        health_bar.setOutlineThickness(0.f);
        health_bar.setScale(sf::Vector2f(hp, 1));
        health_bar.setFillColor(sf::Color::Green);
        target.draw(health_bar);

        
        std::string bullet_string = std::to_string(bullets);

        uint32_t i = 0;
        for (const auto& c : bullet_string)
        {
            int32_t num = (c - '0') - 1;
            if (num < 0) num = 9;

            m_ammo.setTextureRect(sf::IntRect({ 0, 16 * num }, { 16, 16 }));

            m_ammo.setColor(sf::Color::Black);
            m_ammo.setPosition(rect.getPosition() + sf::Vector2f(i * 10, 0));
            m_ammo.move(sf::Vector2f(2, 2));
            target.draw(m_ammo);

            m_ammo.setColor(sf::Color::White);
            m_ammo.setPosition(rect.getPosition() + sf::Vector2f(i++ * 10, 0));
            target.draw(m_ammo);
        }
    }
}