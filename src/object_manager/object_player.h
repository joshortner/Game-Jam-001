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

        sf::Vector2f get_pos() const { return rect.getPosition(); }

    private:
        std::bitset<4> m_movement;
        const float K = 5.f;
        float m_max_vel = 0.5f;
        sf::Vector2f m_velocity;
        sf::Vector2f m_move_dir;
        sf::RectangleShape rect;
    };  
}