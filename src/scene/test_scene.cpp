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
    m_player = m_game_state.m_obj_mgr.create<object_player>(*this);

    camera_pos = (decltype(camera_pos))dimensions / 2.0;
}

void test_scene::on_update(double dt) 
{
    sf::Vector2f room_coordinates = sf::Vector2f(
        m_player->get_pos().x / (float)get_size().x,
        m_player->get_pos().y / (float)get_size().y
    );

    // hacking this to make it care about negative coordinates
    if (room_coordinates.x < 0) room_coordinates.x -= 1.f;
    if (room_coordinates.y < 0) room_coordinates.y -= 1.f;
    room_coordinates.x = (float)(int)room_coordinates.x;
    room_coordinates.y = (float)(int)room_coordinates.y;

    std::cout << room_coordinates.x << ", " << room_coordinates.y << "\n";

    target_pos = { 
        (double)get_size().x / 2.0 + (double)get_size().x * (double)room_coordinates.x, 
        (double)get_size().y / 2.0 + (double)get_size().y * (double)room_coordinates.y };

    camera_pos += (target_pos - camera_pos) * 0.7 * 5.0 * dt;
    m_surface.setView(sf::View((sf::Vector2f)camera_pos, (sf::Vector2f)get_size()));
}

void test_scene::on_render() 
{
    m_surface.clear();
}

}