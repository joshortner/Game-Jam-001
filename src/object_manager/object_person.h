#pragma once

#include "object_itf.h"

#include <SFML/Graphics.hpp>

namespace bk
{
    class object_person :
        public object_itf
    {
    public:
        object_person(scene& scene, const sf::Texture& texture);

        void on_update(double dt) override;
        void on_render(sf::RenderTarget& target) override;
        void on_event(event e) override;

        TYPE_ENUM(object_type::person);

    private:
        sf::Clock clock;

        sf::Sprite m_sprite;
        float m_random_offset;

        sf::Vector2f m_velocity;
    };
}