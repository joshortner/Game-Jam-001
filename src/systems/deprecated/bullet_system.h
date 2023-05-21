#pragma once

#include "../utility/no_copy.h"
#include "../object_manager/object_player.h"
#include "../event/event.h"

namespace bk
{
    class bullet_system :
        public utility::no_copy
    {
    public:
        bullet_system(scene& scene, object_player** player);

        void on_update(double dt);
        void on_event(const event& event);

    private:
        bool mouse_down = false;
        sf::Texture m_bullet_texture;
        object_player** m_player;
        scene& m_scene;
        sf::Clock m_bullet_clock;
    };
}