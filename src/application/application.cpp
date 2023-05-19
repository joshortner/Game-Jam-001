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

            sf::Event event;
            while (m_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }

            m_window.clear();

            // grab the top scene, if it's done delete it and grab the new
            // top scene
            scene* current_scene = m_scenes.back();
            if (current_scene->get_state() == scene_state::complete)
            {
                delete current_scene;
                m_scenes.pop_back();
                current_scene = m_scenes.back();
            }

            // update all the scenes...
            for (auto* scene : m_scenes)
                scene->on_update(dt);

            // ... but render only the top scene
            current_scene->on_render();

            const sf::Vector2f scale = sf::Vector2f(
                (float)m_window.getSize().x / (float)current_scene->get_size().x,
                (float)m_window.getSize().y / (float)current_scene->get_size().y
            );

            sf::Sprite surface(current_scene->get_texture());
            surface.setScale(scale);
            m_window.draw(surface);

            m_window.display();

            m_window.setTitle("FPS: " + std::to_string((int)(1.0 / dt)));
        }
    }
}