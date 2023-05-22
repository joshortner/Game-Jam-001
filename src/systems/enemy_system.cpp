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
            rect.setOrigin(sf::Vector2f(rect.getSize().x / 2.f, rect.getSize().y / 2.f));
            target.draw(rect);

            sf::RectangleShape health;
            health.setSize(sf::Vector2f(16.f, 4.f));
            health.setFillColor(sf::Color::Red);
            health.setPosition(rect.getPosition());
            health.setOutlineThickness(1.f);
            health.setOutlineColor(sf::Color::Black);
            health.move(sf::Vector2f(0, -7 + hp.offset));
            health.move(rect.getOrigin() * -1.f);
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

        std::vector<flecs::entity> dead_enemies;
        dead_enemies.reserve(f.count());

        // need to iterate through other enemies to push away
        f.each([&world, player, this, &dead_enemies](
            flecs::entity    e_enemy,
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

            sf::FloatRect rect;
            rect.width = 16.f;
            rect.height = 16.f;
            rect.left = transform.position.x;
            rect.top = transform.position.y;

            rect.left -= rect.width / 2.f;
            rect.top -= rect.height / 2.f;

            // do some collision testing with the bullets
            auto bullets = world.filter<
                component::bullet,
                component::transform
            >();

            std::vector<flecs::entity> entities;
            entities.reserve(bullets.count());

            bullets.each([rect, &hp, &entities, &velocity](flecs::entity e, component::bullet bullet, component::transform& transform)
            {
                if (rect.contains(sf::Vector2f(transform.position.x, transform.position.y)))
                {
                    entities.push_back(e);
                    hp.value -= 0.2f;
                    auto* velocity_ptr = e.get<component::velocity>();
                    velocity.x = velocity_ptr->x;
                    velocity.y = velocity_ptr->y;
                }
            });

            for (auto e : entities) e.destruct();

            force.x = dir.x;
            force.y = dir.y;

            hp.offset = sin(this->m_clock.getElapsedTime().asSeconds());

            if (hp.value <= 0.01f) dead_enemies.push_back(e_enemy);
        });

        for (auto e : dead_enemies) e.destruct();
    }
}