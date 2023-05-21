#include "object_button.h"
#include "bullet_killer.h"
#include "common.h"

#include <SimplexNoise.h>
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

object_button_mm_start::object_button_mm_start(
    scene &scene,
    sf::Texture *p_on,
    sf::Texture *p_off
) : object_button(scene), mp_button_on(p_on), mp_button_off(p_off), m_on(false)
{
    BK_ASSERT(mp_button_on, "nullptr");
    BK_ASSERT(mp_button_off, "nullptr");

    m_position = { 300, 275 };
    m_scale = { 2.5f, 2.5f };
}

void object_button_mm_start::on_update(double dt) 
{
    float scale       = 100.f;    
    float lacunarity  = 1.99f;
    float persistance = 0.5f;
    static const SimplexNoise simplex(0.1f/scale, 0.5f, lacunarity, persistance); // Amplitude of 0.5 for the 1st octave : sum ~1.0f
    static const int octaves = static_cast<int>(5 + std::log(scale)); // Estimate number of octaves needed for the current scale

    static double ms_passed = 0.0f;
    ms_passed += dt;

    float perlin = simplex.noise(ms_passed) + 0.5f;
    static bool last_hover = m_is_hovered;

    if (m_is_hovered) {
        //m_on = true;
        
        if (last_hover != m_is_hovered) {
            m_on = true;
        }
        else { 
            if (perlin >= 0.0f) {
                m_on = !m_on;
            }
        }
    
    }
    else {
        m_on = false;
    }

    last_hover = m_is_hovered;
}

void object_button_mm_start::on_render(sf::RenderTarget& target, render_pass pass) 
{
    switch (pass)
    {
        case render_pass::draw:
        case render_pass::bloom:
        {
            if (!m_on && pass == render_pass::bloom) { return; }
            sf::Texture *p_texture = m_on ? mp_button_on : mp_button_off;
            sf::Sprite start_sprite(*p_texture);
            start_sprite.setPosition(m_position);
            start_sprite.setScale(m_scale);
            target.draw(start_sprite);
        }
    }
}

sf::FloatRect object_button_mm_start::get_bounding_box() const 
{
    sf::Sprite sprite(*mp_button_on);
    sprite.setPosition(m_position);
    sprite.setScale(m_scale);
    return sprite.getGlobalBounds();
}

void object_button_mm_start::on_click() 
{
    printf("Start!\n");
}

}