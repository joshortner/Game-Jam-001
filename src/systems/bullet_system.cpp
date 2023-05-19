#include "bullet_system.h"

#include "../object_manager/object_bullet.h"
#include "../bullet_killer.h"
#include "scene/scene.h"
#include "application.h"

namespace bk
{
    bullet_system::bullet_system(scene& scene, object_player** player) :
        m_scene(scene),
        m_player(player)
    {   
        if (!m_bullet_texture.loadFromFile(get_texture_path(texture::bullet)))
            std::cout << "Error loading bullet texture\n";
    }

    void bullet_system::on_event(const event& event)
    {
        if (event.m_type == event_type::mouse_button_pressed)
            if (event.m_mouse_button.button == sf::Mouse::Button::Left) mouse_down = true;
        else if (event.m_type == event_type::mouse_button_released)
            if (event.m_mouse_button.button == sf::Mouse::Button::Left) mouse_down = false;
    }

    void bullet_system::on_update(double dt)
    {
        if (mouse_down)
        {
            if (m_bullet_clock.getElapsedTime().asSeconds() > 0.1)
            {
                sf::Vector2i mouse_position = sf::Mouse::getPosition(application::get().get_window());
                sf::Vector2f scale = application::get().get_scale(m_scene);
                sf::Vector2f scaled_mouse((float)mouse_position.x / scale.x, (float)mouse_position.y / scale.y);

                sf::Vector2f dir = (scaled_mouse - (*m_player)->get_pos()).normalized();

                float mag   = dir.length();
                float angle = dir.angle().asRadians() + ((float)(rand() % 100) / 50.f - 1.f) * 0.1f;
                sf::Vector2f final_dir = sf::Vector2f(
                    mag * cos(angle),
                    mag * sin(angle)
                );
                
                m_scene.get_game_state().m_obj_mgr.create<object_bullet>(m_scene, (*m_player)->get_pos(), final_dir, m_bullet_texture);
                m_bullet_clock.restart();
            }
        }

        //std::vector<object_itf *> objects;
        //m_scene.get_game_state().m_obj_mgr.get_object_type(objects, object_type::bullet);
    }
}