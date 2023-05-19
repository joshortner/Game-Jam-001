#pragma once

#include <bitset>

#include "object_itf.h"

namespace bk
{
    class object_player :
        public object_itf
    {
    public:
        object_player(scene& scene);

        void on_update(double dt);
        void on_render(sf::RenderTarget& target);
        void on_event(event e);

    private:
        std::bitset<4> m_movement;
        sf::Vector2f move_dir;
        sf::RectangleShape rect;
    };  
}