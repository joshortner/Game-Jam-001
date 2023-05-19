#pragma once

#include "../utility/no_copy.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace bk
{
    class scene;

    class application : 
        public utility::no_copy
    {
        sf::RenderWindow    mwindow;
        std::vector<scene*> mscenes;

    public:
        application(const sf::Vector2u& dimensions, scene* const start_scene);

        void run();
    };
}