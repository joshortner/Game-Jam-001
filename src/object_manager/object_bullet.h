#pragma once

#include "object_itf.h"

namespace bk
{
    class object_bullet :
        public object_itf
    {
    public:
        object_bullet(scene& scene, const sf::Vector2f& pos, const sf::Vector2f& dir, sf::Texture& texture, double lifetime = 10.0);
        virtual ~object_bullet() = default;
        
        virtual void on_update(double dt) override;
        void on_render(sf::RenderTarget& target, render_pass pass);
        void on_event(event e);

        void set_done(bool done) { m_done = done; }
        bool get_done() const { return m_done; }

        sf::Vector2f get_pos() const { return m_pos; }

        TYPE_ENUM(object_type::bullet);

    protected:
        sf::Clock clock;
        double m_lifetime;
        bool m_done = false;
        sf::Vector2f m_pos;
        const sf::Vector2f m_direction;
        sf::Texture& m_texture;
    };
}
