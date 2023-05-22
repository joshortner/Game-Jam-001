#include "room_system.h"

#include "../object_manager/components.h"

namespace bk
{
    room_system::room_system(flecs::entity player) :
        m_player(player)
    {

    }

    void room_system::on_render(sf::RenderTarget& target, render_pass pass, flecs::world& world)
    {
        /*
        sf::Vector2f room_coordinates = sf::Vector2f(
            m_player.get<component::transform>()->position.x / (float)target.getSize().x,
            m_player.get<component::transform>()->position.y / (float)target.getSize().y
        );

        // hacking this to make it care about negative coordinates
        if (room_coordinates.x < 0) room_coordinates.x -= 1.f;
        if (room_coordinates.y < 0) room_coordinates.y -= 1.f;
        //room_coordinates.x = (float)(int)room_coordinates.x;
        //room_coordinates.y = (float)(int)room_coordinates.y;
        sf::Vector2i map_coordinates = (sf::Vector2i)room_coordinates;

        const sf::Vector2i adjacent[] = {
            sf::Vector2i( 1,  0) + map_coordinates,
            sf::Vector2i(-1,  0) + map_coordinates,
            sf::Vector2i( 0,  1) + map_coordinates,
            sf::Vector2i( 0, -1) + map_coordinates,
            sf::Vector2i( 0,  0) + map_coordinates
        };
        const uint32_t SIZE = sizeof(adjacent) / sizeof(sf::Vector2i);

        int32_t indices[SIZE];
        std::memset(indices, -1, sizeof(indices));

        //std::vector<object_room*> rooms;
        //m_scene.get_game_state().m_obj_mgr.get_object_type(rooms);
        auto f = world.filter<component::room, component::map_position>();

        uint32_t i = 0;
        f.each([SIZE, adjacent, &indices, &i](flecs::entity e, component::room r, component::map_position& transform)
        {
            for (uint32_t j = 0; j < SIZE; j++)
                if (sf::Vector2i(transform.x, transform.y) == adjacent[j])
                {
                    indices[j] = i++;
                    break;
                }
        });
        
        for (uint32_t i = 0; i < SIZE; i++)
            if (indices[i] == -1)*/

                //m_scene.get_game_state().m_obj_mgr.create<object_room>(m_scene, adjacent[i])->set_z(1000.f);
    }

    void room_system::on_update(double dt, flecs::world&)
    {

    }
}