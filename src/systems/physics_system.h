#pragma once

#include "system.h"

namespace bk
{
    class physics_system :
        public system
    {
    public:
        void on_update(double dt, flecs::world& world) override;
    };
}   