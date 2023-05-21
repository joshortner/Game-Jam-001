#pragma once

#include "system.h"

namespace bk
{
    class enemy_system :
        public system
    {
        sf::Clock m_clock;

    public:
        void on_render(sf::RenderTarget& target, render_pass pass, flecs::world& world) override;
        void on_update(double dt, flecs::world& world) override;
    };
}