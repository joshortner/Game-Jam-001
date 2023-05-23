#pragma once

#include "system.h"

namespace bk
{
    class room_system :
        public system
    {
    public:
        room_system(flecs::entity player);

        void on_render(sf::RenderTarget& target, render_pass pass, flecs::world& world);
        void on_update(double dt, flecs::world&);

    private:
        flecs::entity m_player;
    };
}