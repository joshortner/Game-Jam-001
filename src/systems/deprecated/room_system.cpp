#include "room_system.h"

namespace bk
{
    room_system::room_system(scene& scene, object_player** player) :
        m_scene(scene),
        m_player(player)
    {
        
    }

    void room_system::on_update(double dt, const sf::Vector2i& map_coordinates)
    {
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

        std::vector<object_room*> rooms;
        m_scene.get_game_state().m_obj_mgr.get_object_type(rooms);

        for (uint32_t i = 0; i < rooms.size(); i++)
            for (uint32_t j = 0; j < SIZE; j++)
                if (rooms[i]->map_coordinates() == adjacent[j])
                {
                    indices[j] = i;
                    break;
                }
        
        for (uint32_t i = 0; i < SIZE; i++)
            if (indices[i] == -1)
                m_scene.get_game_state().m_obj_mgr.create<object_room>(m_scene, adjacent[i])->set_z(1000.f);
    }
}