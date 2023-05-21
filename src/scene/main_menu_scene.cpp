#include "main_menu_scene.h"
#include "object_button.h"
#include "bullet_killer.h"
#include "common.h"

namespace bk
{

main_menu_scene::main_menu_scene(const sf::Vector2u& dimensions) :
    scene(dimensions), m_hover_system(*this)
{
// Load Resources
    BK_ASSERT(m_start_button_on.loadFromFile(get_texture_path(texture::start_button_on)), "Unable to load texture");
    BK_ASSERT(m_start_button_off.loadFromFile(get_texture_path(texture::start_button_off)), "Unable to load texture");
    BK_ASSERT(m_gun_0.loadFromFile(get_texture_path(texture::main_menu_gun_0)), "Unable to load texture");

// Create objects
    object_button_mm_start *p_start_button = m_game_state.m_obj_mgr.create<object_button_mm_start>(
        *this, &m_start_button_on, & m_start_button_off);
}

void main_menu_scene::on_update(double dt) 
{
    // Systems
    m_hover_system.on_update(dt);
}

void main_menu_scene::on_render() 
{
    sf::Sprite gun_sprite(m_gun_0);
    m_surface.draw(gun_sprite);
}

}