#pragma once

#include <bitset>

#include "object_itf.h"

namespace bk
{
    class object_player :
        public object_itf
    {
    public:
        object_player(scene& scene, const sf::Texture& bullet);

        void on_update(double dt);
        void on_render(sf::RenderTarget& target);
        void on_event(event e);

        void shoot(uint32_t bullet = 1) { if (bullets) bullets -= bullet; }
        uint32_t get_bullets() const { return bullets; }

        sf::Vector2f get_pos() const { return rect.getPosition(); }

        TYPE_ENUM(object_type::player);

    private:
        sf::Sprite m_ammo;

        std::bitset<4> m_movement;
        const float K = 5.f;
        float m_max_vel = 1000.f;
        sf::Vector2f m_velocity;
        sf::Vector2f m_move_dir;
        sf::RectangleShape rect;

        uint32_t bullets = 100;
    };  
}