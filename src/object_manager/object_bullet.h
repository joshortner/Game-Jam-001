#pragma once

#include "object_itf.h"

namespace bk
{
    class object_bullet :
        public object_itf
    {
    public:
        object_bullet(scene& scene, const sf::Vector2f& pos, const sf::Vector2f& dir, sf::Texture& texture);

        void on_update(double dt);
        void on_render(sf::RenderTarget& target, render_pass pass);
        void on_event(event e);

    private:
        sf::Vector2f m_pos;
        const sf::Vector2f m_direction;
        sf::Texture& m_texture;
    };
}