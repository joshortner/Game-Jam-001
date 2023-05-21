#pragma once

#include "object_itf.h"

#include "bullet_killer.h"

namespace bk
{
    class object_room :
        public object_itf
    {
    public:
        object_room(scene& scene);
        ~object_room() = default;

        void on_update(double dt);
        void on_render(sf::RenderTarget& target, render_pass pass);
        void on_event(event e);

    private:
        sf::Texture room_texture;
    };
}