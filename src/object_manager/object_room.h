#pragma once

#include "object_itf.h"

namespace bk
{
    class object_room :
        public object_itf
    {
    public:
        object_room(scene& scene);
        ~object_room() = default;

        void on_update(double dt);
        void on_render(sf::RenderTarget& target);
        void on_event(event e);

    private:
        sf::Texture room_texture;
    };
}