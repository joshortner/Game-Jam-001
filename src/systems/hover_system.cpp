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
    printf("mouse: %d %d\n", mouse_position.x, mouse_position.y);
    
    for (object_itf* p_obj : objects) {
        sf::FloatRect rect(p_obj->m_position, p_obj->m_scale);
        printf("Obj: %f %f\n", rect.getPosition().x, rect.getPosition().y);
        if (rect.contains({ (float)mouse_position.x, (float)mouse_position.y })) {
            printf("Hovered\n");
        }
    }
}

}