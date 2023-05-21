#include "ecs_scene.h"

#include "../systems/enemy_system.h"
#include "../systems/physics_system.h"
#include "../object_manager/components.h"

namespace bk
{
    ecs_scene::ecs_scene(const sf::Vector2u& dimensions) :
        scene(dimensions)
    {
        get_texture(texture::bullet);

        add_system<enemy_system>();
        add_system<physics_system>();

        add_object<object_player>(*this, m_world);


        for (uint32_t i = 0; i < 10; i++)
        {
            auto enemy = m_world.entity();
            enemy.set(component::transform{
                .position = { (rand() % 100) / 100.f * dimensions.x, (rand() % 100) / 100.f * dimensions.y },
                .scale = { 1, 1 },
                .rotation = 0
            })
            .set(component::velocity{
                .x = 0,
                .y = 0
            })
            .set(component::force{
                .k = 5.f,
                .max_velocity = 150.f,
                .x = 0,
                .y = 0,
                .m = 1
            })
            .set(component::hp{
                .value = 1,
                .max = 1
            })  
            .add<component::enemy>();
        }
    }

    void ecs_scene::on_update(double dt)
    {
        //player.on_update(dt, get_world());
    }
}