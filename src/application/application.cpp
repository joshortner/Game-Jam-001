#include "application.h"
#include "../scene/scene.h"

namespace bk
{
    application::application(const sf::Vector2u& dimensions, scene* const start_scene) :
        m_window(sf::VideoMode(dimensions), "whats up"),
        m_scenes({ start_scene })
    {

    }

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

            sf::Event event;
            while (m_window.pollEvent(event))
            {
                handle_event(event);
                current_scene->on_event(convert_sfml_event(event));
            }

            m_window.clear();

            // update only the top scene...
            current_scene->on_update(dt);
            current_scene->update_objects(dt);

            // ... but render every other scene
            for (auto* scene : m_scenes)
            {
                scene->on_render();
                scene->render_objects();

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
}