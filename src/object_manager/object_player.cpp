#include "object_player.h"

//#include "object_bullet.h"
#include "../scene/scene.h"
#include "../application/application.h"

#include <iostream>

namespace bk
{
    object_player::object_player(scene& scene, flecs::world& world) :
        m_player(world.entity()),
        m_scene(scene)
    {
        m_player.set(component::transform{ 
                .position = { 0, 0 },
                .scale = { 1, 1 },
                .rotation = 0
            })
            .set(component::velocity{ 
                .x = 0, 
                .y = 0 
            })
            .set(component::force{ 
                .m = 1,
                .x = 0,
                .y = 0,
                .k = 5.f,
                .max_velocity = 1000.f
             })
            .set(component::rectangle {
                .width = 16,
                .height = 16,
                .color = sf::Color::Red
            }).set(component::ammo {
                .count = 100
            })
            .set(component::hp{
                .value = 1,
                .max = 1
            })
            .set(component::scriptable {
                .object = static_cast<component::scriptable_object*>(this)
            })
            .set(component::input {
                .object = static_cast<component::input_object*>(this)
            })
            .add<component::player>();
    }

    void object_player::on_update(double dt, flecs::world& world)
    {
        const float m = 1.f;
        auto position  = m_player.get<component::transform>()->position;
        component::force* force = m_player.get_mut<component::force>();
        
        force->x = 0; force->y = 0;
        const float mag = force->max_velocity * force->k;
        if (m_input[0]) force->y -= mag;
        if (m_input[1]) force->y += mag;
        if (m_input[2]) force->x -= mag;
        if (m_input[3]) force->x += mag;

        if (m_input[4] && clock.getElapsedTime().asSeconds() >= 0.06) 
        {
            // get direction from position to mouse
            const sf::Vector2i mouse_position = sf::Mouse::getPosition(application::get().get_window());
            const sf::Vector2f scale = application::get().get_scale(m_scene);
            const sf::Vector2f scaled_mouse((float)mouse_position.x / scale.x, (float)mouse_position.y / scale.y);
            const sf::Vector2f diff = m_scene.get_view().getCenter() - (sf::Vector2f)m_scene.get_size() / 2.f;
            const sf::Vector2f player_pos = sf::Vector2f(position.x, position.y);
            const sf::Vector2f dir = (scaled_mouse - (player_pos - diff)).normalized().rotatedBy(sf::radians(((rand() % 1000) / 1000.f * 2.f - 1.f) * 0.1f));

            auto bullet = world.entity();
            bullet.set(component::transform {
                .position = position,
                .scale = { 1, 1 },
                .rotation = atan2f(dir.y, dir.x)
            })
            .set(component::velocity {
                .x = dir.x * 400.f,
                .y = dir.y * 400.f
            })
            .set(component::sprite {
                .texture = m_scene.get_texture(texture::bullet)
            })
            .add<component::bullet>();

            clock.restart();
        }
    }

    void object_player::on_event(bk::event e)
    {
        if (e.m_type == event_type::key_press)
        {
            switch (e.m_key.code)
            {
            case sf::Keyboard::W: m_input[0] = 1; break;
            case sf::Keyboard::S: m_input[1] = 1; break;
            case sf::Keyboard::A: m_input[2] = 1; break;
            case sf::Keyboard::D: m_input[3] = 1; break;
            case sf::Keyboard::R: m_player.get_mut<component::ammo>()->count = 100; break;
            }
        }
        else if (e.m_type == event_type::key_release)
        {
            switch (e.m_key.code)
            {
            case sf::Keyboard::W: m_input[0] = 0; break;
            case sf::Keyboard::S: m_input[1] = 0; break;
            case sf::Keyboard::A: m_input[2] = 0; break;
            case sf::Keyboard::D: m_input[3] = 0; break;
            }
        }

        if (e.m_type == event_type::mouse_button_pressed)
            if (e.m_mouse_button.button == sf::Mouse::Button::Left) m_input[4] = 1;
        if (e.m_type == event_type::mouse_button_released)
            if (e.m_mouse_button.button == sf::Mouse::Button::Left) m_input[4] = 0;
    }
    
    /*
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
    }*/
}