#include "bullet_system.h"

#include "../object_manager/components.h"

namespace bk
{
    void bullet_system::on_update(double dt, flecs::world& world)
    {
        auto player_f = world.filter<component::player>();
        assert(player_f.count());
        auto player_e = player_f.first();
        
        const sf::Vector2f player_pos = sf::Vector2f(
            player_e.get<component::transform>()->position.x,
            player_e.get<component::transform>()->position.y
        );

        std::vector<flecs::entity> dead_bullets;

        auto bullets = world.filter<component::bullet, component::transform>();
        bullets.each([player_pos, &dead_bullets](flecs::entity e, component::bullet b, component::transform& transform)
        {
            const float distance = (sf::Vector2f(
                transform.position.x,
                transform.position.y
            ) - player_pos).length();

            if (distance >= 1000) dead_bullets.push_back(e);
        });

        for (auto e : dead_bullets) e.destruct();
    }
}