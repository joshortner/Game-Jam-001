#pragma once

#include "../bullet_killer.h"
#include <SFML/Graphics.hpp>
#include <flecs.h>

namespace bk
{
    class system
    {
    public:
        virtual void on_render(sf::RenderTarget& target, render_pass pass, flecs::world& world) { };
        virtual void on_update(double dt, flecs::world&) = 0;
    };
}