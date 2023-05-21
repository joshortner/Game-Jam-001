#pragma once

#include "object_player.h"

namespace bk
{
    class object_enemy :
        public object_itf
    {
    public:
        object_enemy(scene& scene, object_player* player, const sf::Vector2f& pos, const sf::Texture& bullet_texture);

        void on_update(double dt) override;
        void on_render(sf::RenderTarget& target) override;
        void on_event(event e) override;

        sf::Vector2f get_pos() const { return m_rect.getPosition(); }

        float get_hp() const { return hp; }

        TYPE_ENUM(object_type::enemy);

    private:
        sf::Vector2f m_velocity;
        sf::Vector2f m_force;

        sf::Clock clock;

        float random_t_offset = 0.f;
        float hp_offset = 0.f;
        float hp = 1.f;

        sf::RectangleShape m_rect;

        const sf::Texture& m_bullet_texture;

        object_player* m_player;
    };
}