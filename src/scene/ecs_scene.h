#pragma once

#include "../object_manager/object_player.h"
#include "scene.h"

namespace bk
{
    class ecs_scene : 
        public scene
    {
    public:
        ecs_scene(const sf::Vector2u& dimensions);

        void on_update(double dt) override;

    private:
        object_player player;
    };
}