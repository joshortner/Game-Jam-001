#include "application.h"
#include "bullet_killer.h"
#include "../object_manager/object_itf.h"
#include "scene.h"
#include "common.h"

#include "../object_manager/components.h"

#include <SFML/Graphics.hpp>

#include <stdio.h>

namespace bk
{

    application& application::create(const sf::Vector2u& dimensions, scene* const start_scene)
    {
        if (sp_application == nullptr) {
            sp_application = new application(dimensions, start_scene);
        }
        return *sp_application;
    }

    application::application(const sf::Vector2u& dimensions, scene* const start_scene) :
        m_window(sf::VideoMode(dimensions), "Bullet Killer"),
        m_scenes({ start_scene })
    {
        m_window.setFramerateLimit(60);
        BK_ASSERT(sf::Shader::isAvailable(), "Shaders not supported");
    }

    application::~application()
    {   }

    void application::run()
    {
        sf::Clock frame_clock;
        while (m_window.isOpen() && m_scenes.size())
        {
            double dt = frame_clock.restart().asSeconds();

            // grab the top scene, if it's done delete it and grab the new
            // top scene
            scene* current_scene = m_scenes.back();
            if (current_scene->get_state() == scene_state::complete)
            {
                delete current_scene;
                m_scenes.pop_back();
                current_scene = m_scenes.back();
            }

            const auto& objects = current_scene->get_objects();

            sf::Event event;
            while (m_window.pollEvent(event))
            {
                handle_event(event);
                bk::event bk_event = convert_sfml_event(event);
                current_scene->on_event(bk_event);

                for (auto* object : objects) object->on_event(bk_event);
            }

            m_window.clear();
        
            for (auto* object : objects)
                object->on_update(dt, current_scene->get_world());

            const auto& systems = current_scene->get_systems();
            for (auto* system : systems)
                system->on_update(dt, current_scene->get_world());

            // ... but render every other scene
            for (auto* scene : m_scenes)
            {
                //scene->on_render();
                scene->render_objects();
                const auto& systems = scene->get_systems();
                for (auto* system : systems)
                    system->on_render(scene->get_render_texture(), render_pass::draw, scene->get_world());

                const sf::Vector2f scale = sf::Vector2f(
                    (float)m_window.getSize().x / (float)scene->get_size().x,
                    (float)m_window.getSize().y / (float)scene->get_size().y
                );

                sf::Sprite surface(scene->get_texture());                
                surface.setScale(scale);
                m_window.draw(surface);
            }

            m_window.display();

            m_window.setTitle("FPS: " + std::to_string((int)(1.0 / dt)));
        }

        for (scene* scene : m_scenes) delete scene;
        m_scenes.clear();
    }

    void application::handle_event(sf::Event e) 
    {
        // Handle events at application level
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
    }

    event application::convert_sfml_event(sf::Event e) const
    {
        event new_event;
        switch (e.type) 
        {
            case sf::Event::Closed: new_event.m_type = event_type::close; break;
            case sf::Event::KeyPressed:
            {
                new_event.m_type = event_type::key_press;
                new_event.m_key = e.key;
                break;
            } 
            case sf::Event::KeyReleased:
            {
                new_event.m_type = event_type::key_release;
                new_event.m_key = e.key;
                break;
            }
            case sf::Event::MouseButtonPressed: 
            {
                new_event.m_type         = event_type::mouse_button_pressed; 
                new_event.m_mouse_button = e.mouseButton; 
                break;
            }
            case sf::Event::MouseButtonReleased: 
            {
                new_event.m_type         = event_type::mouse_button_released; 
                new_event.m_mouse_button = e.mouseButton; 
                break;
            }
            case sf::Event::MouseMoved:
            {
                new_event.m_type       = event_type::mouse_moved;
                new_event.m_mouse_move = e.mouseMove;
                break;
            }
            default: new_event.m_type = event_type::unknown;
        }
        return new_event;
    }

    sf::Vector2f application::get_scale(scene& scene) const
    {
        return sf::Vector2f(
            (float)m_window.getSize().x / (float)scene.get_size().x,
            (float)m_window.getSize().y / (float)scene.get_size().y
        );
    }
}