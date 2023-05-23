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
        static void destroy() { delete sp_application; }
        static sf::ContextSettings get_context_settings();

        scene& get_current_scene() const { return *m_scenes.back(); }

        void run();
        sf::RenderWindow& get_window() { return m_window; }
        sf::Vector2f get_scale(scene& scene) const;

    private:

        application(const sf::Vector2u& dimensions, scene* const start_scene);
        ~application();

    private:

        void handle_event(sf::Event e);
        event convert_sfml_event(sf::Event e) const;

        sf::ContextSettings m_contextSettings;
        sf::RenderWindow    m_window;
        std::vector<scene*> m_scenes;

    private:

        static inline application* sp_application = nullptr;
    
    };
}