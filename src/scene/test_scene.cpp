#include "test_scene.h"

#include "object_npc.h"
#include "../bullet_killer.h"
#include "../animation/node_interpolates.h"
#include "../object_manager/object_enemy.h"
#include "../object_manager/object_room.h"
#include "../object_manager/object_player.h"

#include <iostream>

namespace bk
{
test_scene::test_scene(const sf::Vector2u& dimensions) :
    scene(dimensions),
    m_bullet_system(*this, &m_player),
    m_room_system(*this, &m_player)
{
    if (!m_ammo_texture.loadFromFile(get_texture_path(texture::numbers)))
        std::cout << "Failed to load numbers texture\n";

    m_player = m_game_state.m_obj_mgr.create<object_player>(*this, m_ammo_texture);

    for (uint32_t i = 0; i < 10; i++)
        m_game_state.m_obj_mgr.create<object_enemy>(*this, m_player, sf::Vector2f(
            (rand() % 100) / 100.f * dimensions.x,
            (rand() % 100) / 100.f * dimensions.y
        ));

    camera_pos = (decltype(camera_pos))dimensions / 2.0;
}

void test_scene::on_update(double dt) 
{
    m_bullet_system.on_update(dt);

    std::vector<object_enemy*> enemies;
    get_game_state().m_obj_mgr.get_object_type(enemies);
    for (auto* enemy : enemies)
    {
        enemy->set_z(enemy->get_pos().y / -100.f);
        if (enemy->get_hp() <= 0)
        {
            get_game_state().m_obj_mgr.remove_object(enemy);
            m_game_state.m_obj_mgr.create<object_enemy>(*this, m_player, sf::Vector2f(
                (rand() % 100) / 100.f * get_size().x,
                (rand() % 100) / 100.f * get_size().y
            ));
        }
    }

    sf::Vector2f room_coordinates = sf::Vector2f(
        m_player->get_pos().x / (float)get_size().x,
        m_player->get_pos().y / (float)get_size().y
    );

    // hacking this to make it care about negative coordinates
    if (room_coordinates.x < 0) room_coordinates.x -= 1.f;
    if (room_coordinates.y < 0) room_coordinates.y -= 1.f;
    room_coordinates.x = (float)(int)room_coordinates.x;
    room_coordinates.y = (float)(int)room_coordinates.y;
    m_room_system.on_update(dt, (sf::Vector2i)room_coordinates);

    target_pos = { 
        (double)get_size().x / 2.0 + (double)get_size().x * (double)room_coordinates.x, 
        (double)get_size().y / 2.0 + (double)get_size().y * (double)room_coordinates.y 
    };

    camera_pos += (target_pos - camera_pos) * 0.9 * 5.0 * dt;
    set_view(sf::View((sf::Vector2f)camera_pos, (sf::Vector2f)get_size()));
}

void test_scene::on_event(event event) 
{
    m_game_state.m_obj_mgr.on_event(event);
    m_bullet_system.on_event(event);
}

void test_scene::on_render() 
{
    m_surface.clear();
}

}