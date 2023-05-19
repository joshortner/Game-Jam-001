#pragma once

#include "../utility/no_copy.h"
#include "event.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace bk
{
    class scene;

    class application : 
        public utility::no_copy
    {
    public:
        application(const sf::Vector2u& dimensions, scene* const start_scene);

        void run();

    private:

        void handle_event(sf::Event e);
        event convert_sfml_event(sf::Event e) const;

        sf::RenderWindow    m_window;
        std::vector<scene*> m_scenes;
    
    };
}