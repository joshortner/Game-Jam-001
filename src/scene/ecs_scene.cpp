#include "ecs_scene.h"

#include "../systems/enemy_system.h"
#include "../systems/physics_system.h"
#include "../systems/bullet_system.h"
#include "../systems/room_system.h"
#include "../object_manager/components.h"

namespace bk
{
    ecs_scene::ecs_scene(const sf::Vector2u& dimensions) :
        scene(dimensions),
        player(*this, m_world)
    {
        get_texture(texture::bullet);

        add_system<enemy_system>();
        add_system<physics_system>();
        add_system<bullet_system>();
        add_system<room_system>(player.get_entity());

        //add_object<object_player>(*this, m_world);

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
        sf::Vector2f room_coordinates = sf::Vector2f(
            player.get_entity().get<component::transform>()->position.x / (float)get_size().x,
            player.get_entity().get<component::transform>()->position.y / (float)get_size().y
        );

        // hacking this to make it care about negative coordinates
        if (room_coordinates.x < 0) room_coordinates.x -= 1.f;
        if (room_coordinates.y < 0) room_coordinates.y -= 1.f;
        room_coordinates.x = (float)(int)room_coordinates.x;
        room_coordinates.y = (float)(int)room_coordinates.y;

        const sf::Vector2f target_pos = { 
            (float)get_size().x / 2.f + (float)get_size().x * (float)room_coordinates.x, 
            (float)get_size().y / 2.f + (float)get_size().y * (float)room_coordinates.y 
        };

        camera_pos += (target_pos - camera_pos) * 0.9f * 5.0f * (float)dt;
        set_view(sf::View((sf::Vector2f)camera_pos, (sf::Vector2f)get_size()));
    }
}