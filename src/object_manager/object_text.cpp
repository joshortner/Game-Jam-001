#include "object_text.h"

namespace bk
{
    object_text::object_text(scene& scene, const std::string& text, const sf::Texture& texture) :
        object_itf(scene, object_type::text),
        m_texture(texture),
        m_text(text)
    {   }

    void object_text::on_update(double dt)
    {

    }

    void object_text::on_render(sf::RenderTarget& target)
    {
        sf::Sprite sprite(m_texture);
        sprite.setScale(m_scale);
        
        for (uint32_t i = 0; i < m_text.length(); i++)
        {
            const int32_t index = m_text[i] - 'A';
            if (index < 0) continue;

            sprite.setTextureRect(sf::IntRect(
                { 16 * index, 0 },
                { 16, 16 }
            ));

            sprite.setPosition(
                m_position + 
                sf::Vector2f(12 * i, 0) * m_scale.x - 
                sf::Vector2f(
                    m_scale.x * 12 * m_text.length() / 2.f,
                    m_scale.y * 16 / 2.f
                )
            );

            target.draw(sprite);
        }
    }

    void object_text::on_event(event e)
    {

    }
}