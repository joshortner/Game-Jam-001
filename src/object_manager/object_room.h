#pragma once

#include "object_itf.h"

namespace bk
{
    class object_room :
        public object_itf
    {
    public:
        object_room(scene& scene, sf::Vector2i coordinates);
        ~object_room() = default;

        void on_update(double dt);
        void on_render(sf::RenderTarget& target);
        void on_event(event e);

        sf::Vector2i map_coordinates() { return m_coordinates; }

        inline static const object_type Type = object_type::room;

    private:
        const sf::Vector2i m_coordinates;
        sf::Texture room_texture;
    };
}