#include "physics_system.h"

#include <iostream>

#include "../object_manager/components.h"

namespace bk
{
    void physics_system::on_update(double dt, flecs::world& world)
    {
        using namespace component;

        auto f = world.filter<force, transform, velocity>();
        f.each([dt](force& force, transform& transform, velocity& velocity) 
        {
            sf::Vector2f a = (sf::Vector2f(force.x, force.y) - 3.f * force.k * sf::Vector2f(velocity.x, velocity.y)) / force.m;
            velocity.x += a.x * (float)dt;
            velocity.y += a.y * (float)dt;
        });

        auto vel_transform = world.filter<transform, velocity>();
        vel_transform.each([dt](transform& transform, velocity& velocity) 
        {
            transform.position.x += velocity.x * dt;
            transform.position.y += velocity.y * dt;
        });
    }
}