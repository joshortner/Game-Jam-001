#pragma once

#include "object_itf.h"

namespace bk
{
    class object_text :
        public object_itf
    {
    public:
        object_text(scene& scene, const std::string& text, const sf::Texture& texture);

        void on_update(double dt) override;
        void on_render(sf::RenderTarget& target, render_pass pass) override;
        void on_event(event e) override;

        const std::string& get_text() const { return m_text; }

        TYPE_ENUM(object_type::text);

    private:
        const std::string m_text;
        const sf::Texture& m_texture;
    };
}