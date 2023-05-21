#pragma once

#include "hover_system.h"
#include "application.h"
#include "object_itf.h"
#include "scene.h"

#include <SFML/Graphics.hpp>

#include <vector>

namespace bk
{

void hover_system::on_update(double dt)
{
    std::vector<object_itf *> objects;
    m_scene.get_game_state().m_obj_mgr.get_object_type(objects, object_type::any);

    sf::Vector2i mouse_position = sf::Mouse::getPosition(application::get().get_window());
    sf::Vector2f scale = application::get().get_scale(m_scene);
    sf::Vector2f scaled_mouse((float)mouse_position.x / scale.x, (float)mouse_position.y / scale.y);
    
    for (object_itf* p_obj : objects) {
        p_obj->set_hovered(p_obj->get_bounding_box().contains(scaled_mouse));
    }
}

}