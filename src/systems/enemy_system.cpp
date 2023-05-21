#include "enemy_system.h"

#include <iostream>
#include "../object_manager/components.h"

namespace bk
{

    void enemy_system::on_render(sf::RenderTarget& target, render_pass pass, flecs::world& world)
    {
        auto f = world.filter<component::enemy, component::transform, component::hp>();
        f.each([&target](component::enemy enemy, component::transform& transform, component::hp& hp)
        {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(16, 16));
            rect.setPosition(sf::Vector2f(transform.position.x, transform.position.y));
            rect.setScale(sf::Vector2f(transform.scale.x, transform.scale.y));
            rect.setRotation(sf::radians(transform.rotation));
            rect.setFillColor(sf::Color::Blue);
            target.draw(rect);

            sf::RectangleShape health;
            health.setSize(sf::Vector2f(16.f, 4.f));
            health.setFillColor(sf::Color::Red);
            health.setPosition(rect.getPosition());
            health.setOutlineThickness(1.f);
            health.setOutlineColor(sf::Color::Black);
            health.move(sf::Vector2f(0, -7 + hp.offset));
            target.draw(health);

            health.setOutlineThickness(0.f);
            health.setScale(sf::Vector2f(hp.value / hp.max, 1));
            health.setFillColor(sf::Color::Green);
            target.draw(health);
        });
    }

    void enemy_system::on_update(double dt, flecs::world& world) 
    {
        auto player_filter = world.filter<component::player>();
        assert(player_filter.count() == 1);
        auto player = player_filter.first();

        auto f = world.filter<
            component::enemy, 
            component::transform, 
            component::force, 
            component::velocity,
            component::hp
        >();

        // need to iterate through other enemies to push away
        f.each([&world, player, this](
            component::enemy enemy, 
            component::transform& transform, 
            component::force& force, 
            component::velocity& velocity,
            component::hp& hp) 
        {
            const float mag = force.max_velocity * force.k;
            const sf::Vector2f player_pos = sf::Vector2f(
                player.get<component::transform>()->position.x,
                player.get<component::transform>()->position.y
            );

            sf::Vector2f dir = (player_pos - sf::Vector2f(
                transform.position.x,
                transform.position.y
            )).normalized() * mag;

            // child of 
            //auto bullets = 

            force.x = dir.x;
            force.y = dir.y;

            hp.offset = sin(this->m_clock.getElapsedTime().asSeconds());
        });
    }
}