#include "object_button.h"
#include "bullet_killer.h"
#include "common.h"

#include <SFML/Graphics.hpp>

#include <stdio.h>

namespace bk
{

object_button::object_button(scene& scene) :
    object_itf(scene, object_type::button)
{ }

void object_button::on_event(event e)
{
    if (e.m_type == event_type::mouse_button_pressed) {
        if (m_is_hovered) {
            on_click();
        }
    }
}

// --------- Main Menu Start Button ---------- //

object_button_mm_start::object_button_mm_start(scene &scene) :
    object_button(scene)
{
    BK_ASSERT(m_texture.loadFromFile(get_texture_path(texture::start_button)), "Unable to load texture");
    m_position = { 100, 100 };
    m_scale = { 0.15f, 0.15f };
}

void object_button_mm_start::on_render(sf::RenderTarget& target) 
{
    sf::Sprite sprite(m_texture);
    sprite.setPosition(m_position);
    sprite.setScale(m_scale);
    target.draw(sprite);
}

void object_button_mm_start::on_click() 
{
    printf("Start!\n");
}

}