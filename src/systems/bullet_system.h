#pragma once

#include "system.h"

namespace bk
{
    class bullet_system :
        public system
    {
    public:
        void on_update(double dt, flecs::world&) override;
    };
}