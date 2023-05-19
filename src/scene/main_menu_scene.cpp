#include "main_menu_scene.h"
#include "object_button.h"

namespace bk
{

main_menu_scene::main_menu_scene(const sf::Vector2u& dimensions) :
    scene(dimensions), m_hover_system(*this)
{
    object_button_mm_start *p_start_button = m_game_state.m_obj_mgr.create<object_button_mm_start>(*this);
}

void main_menu_scene::on_update(double dt) 
{
    // Systems
    m_hover_system.on_update(dt);
}

void main_menu_scene::on_render() 
{

}

}