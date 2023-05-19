#pragma once

#include "../utility/no_copy.h"
#include "event.h"
#include "common.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace bk
{
    class scene;

    class application : 
        public utility::no_copy
    {
    public:

        static application& create(const sf::Vector2u& dimensions, scene* const start_scene);
        static application& get() { BK_ASSERT(sp_application != nullptr, "Applicaiton no initialized"); return *sp_application; }

        void run();
        sf::RenderWindow& get_window() { return m_window; }

    private:

        application(const sf::Vector2u& dimensions, scene* const start_scene);

    private:

        void handle_event(sf::Event e);
        event convert_sfml_event(sf::Event e) const;

        sf::RenderWindow    m_window;
        std::vector<scene*> m_scenes;

    private:

        static inline application* sp_application = nullptr;
    
    };
}