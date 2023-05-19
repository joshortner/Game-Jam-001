#include "test_scene.h"

#include <iostream>

#include "../animation/node_interpolates.h"

#include "../object_manager/object_room.h"
#include "../object_manager/object_player.h"


namespace bk
{
test_scene::test_scene(const sf::Vector2u& dimensions) :
    scene(dimensions)
{
    object_room* room = m_game_state.m_obj_mgr.create<object_room>(*this);
    room->set_z(10.f);
    m_game_state.m_obj_mgr.create<object_player>(*this);

    camera_pos = (decltype(camera_pos))dimensions / 2.0;
    target_pos = { (double)dimensions.x * 3.0 / 2.0, (double)dimensions.y / 2.0 };
}

void test_scene::on_update(double dt) 
{
    camera_pos += (target_pos - camera_pos) * 0.7 * 5.0 * dt;
    m_surface.setView(sf::View((sf::Vector2f)camera_pos, (sf::Vector2f)get_size()));
}

void test_scene::on_render() 
{
    m_surface.clear();
}

}