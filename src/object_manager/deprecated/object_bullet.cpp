#include "object_bullet.h"

namespace bk
{
    object_bullet::object_bullet(scene& scene, const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Texture& texture, double lifetime) :
        object_itf(scene, object_type::bullet),
        m_direction(dir),
        m_pos(pos),
        m_texture(texture),
        m_lifetime(lifetime),
        m_player_owned(false)
    {   }

    void object_bullet::on_update(double dt)
    {
        m_pos += m_direction * 500.f * (float)dt;

        if (clock.getElapsedTime().asSeconds() > m_lifetime)
            set_done(true);
    }

    void object_bullet::on_render(sf::RenderTarget& target, render_pass pass)
    {
        switch (pass)
        {
            case render_pass::draw:
            {
                sf::Sprite bullet(m_texture);
                bullet.setPosition(m_pos);
                bullet.setRotation(sf::radians(atan2f(m_direction.y, m_direction.x)));
                target.draw(bullet);
                break;
            }
        }
    }

    void object_bullet::on_event(event e)
    {

    }
}