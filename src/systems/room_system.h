#pragma once

#include "../object_manager/object_room.h"
#include "../object_manager/object_player.h"
#include "../scene/scene.h"

namespace bk
{
    class room_system
    {
    public:
        room_system(scene& scene, object_player** player);

        void on_update(double dt, const sf::Vector2i& map_coordinates);

    private:
        scene& m_scene;
        object_player** m_player;
    };
}