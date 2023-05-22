#include "object_ui.h"
#include "common.h"
#include "bullet_killer.h"

namespace bk
{

void object_ui_mm_gun::on_update(double dt) 
{
    // tmp
    static double gun_ms_passed = 0.0f;
    gun_ms_passed += (dt * 1000.0f);
    if (gun_ms_passed >= 1500.0f) {
        m_gun_anim_trigger = true;
        gun_ms_passed = 0.0f;
    }
}

void object_ui_mm_gun::on_render(sf::RenderTarget& target, render_pass pass) 
{
    static bool first = true;
    static sf::Texture border_texture;
    static sf::Texture gun_on_texture;
    static sf::Texture gun_off_texture;
    static sf::Texture title_texture;
    if (first) {
        BK_ASSERT(border_texture.loadFromFile(get_texture_path(texture::main_menu_border)), "Unable to load texture");
        BK_ASSERT(gun_on_texture.loadFromFile(get_texture_path(texture::main_menu_gun_on)), "Unable to load texture");
        BK_ASSERT(gun_off_texture.loadFromFile(get_texture_path(texture::main_menu_gun_off)), "Unable to load texture");
        BK_ASSERT(title_texture.loadFromFile(get_texture_path(texture::main_menu_title)), "Unable to load texture");
        first = false;
    }

    sf::Sprite title_sprite(title_texture);
    target.draw(title_sprite);

    sf::Sprite border_sprite(border_texture);
    if (pass == render_pass::draw) {
        border_sprite.setColor(sf::Color(255, 255, 255, 75));
    }
    target.draw(border_sprite);

    static bool up = false;
    if (m_gun_anim_trigger) {
        up = !up;
        m_gun_anim_trigger = false;
    }

    sf::Sprite gun_on_sprite(gun_on_texture);
    sf::Sprite gun_off_sprite(gun_off_texture);
    gun_on_sprite.setColor(sf::Color(255, 255, 255, 200));
    gun_off_sprite.setColor(sf::Color(255, 255, 255, 75));
    
    if (up) {
        gun_on_sprite.setPosition({ 75.0f, -100.0f });
        gun_on_sprite.setRotation(sf::degrees(10.0f));

        gun_off_sprite.setPosition({ 0.0f, 0.0f });
        gun_off_sprite.setRotation(sf::degrees(0.0f));
    }
    else {
        gun_on_sprite.setPosition({ 0.0f, 0.0f });
        gun_on_sprite.setRotation(sf::degrees(0.0f));

        gun_off_sprite.setPosition({ 75.0f, -100.0f });
        gun_off_sprite.setRotation(sf::degrees(10.0f));
    }

    if (pass != render_pass::bloom) {
        target.draw(gun_off_sprite);
    }
    target.draw(gun_on_sprite);
}

void object_ui_mm_gun::on_event(event e) 
{

}

}