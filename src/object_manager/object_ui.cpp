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

class cursive_font
{
public:

    static sf::Sprite get_letter(char letter)
    {
        static const sf::Vector2i letter_size = { 70, 95 };

        load_font_sheet();

        switch (letter)
        {
            case 'B': return sf::Sprite(s_font_sheet, sf::IntRect({ 200, 50 }, letter_size));
            case 'l': return sf::Sprite(s_font_sheet, sf::IntRect({ 335, 240 }, letter_size));
            case 'u': return sf::Sprite(s_font_sheet, sf::IntRect({ 335, 240 }, letter_size));
            default: BK_ASSERT(0, "Letter %d not implemented\n", letter);
        }
    }

private:

    static void load_font_sheet()
    {
        if (!s_loaded) {
            BK_ASSERT(s_font_sheet.loadFromFile(get_texture_path(texture::font_sheet)), "Unable to load texture");
        }
    }

    static inline bool s_loaded = false;
    static inline sf::Texture s_font_sheet; 
};

void object_ui_mm_gun::on_render(sf::RenderTarget& target, render_pass pass) 
{
    static bool first = true;
    static sf::Texture border_texture;
    static sf::Texture gun_on_texture;
    static sf::Texture gun_off_texture;
    static sf::Texture title_texture;

    static sf::Texture font_sheet_texture;

    if (first) {
        BK_ASSERT(border_texture.loadFromFile(get_texture_path(texture::main_menu_border)), "Unable to load texture");
        BK_ASSERT(gun_on_texture.loadFromFile(get_texture_path(texture::main_menu_gun_on)), "Unable to load texture");
        BK_ASSERT(gun_off_texture.loadFromFile(get_texture_path(texture::main_menu_gun_off)), "Unable to load texture");
        BK_ASSERT(title_texture.loadFromFile(get_texture_path(texture::main_menu_title)), "Unable to load texture");
        BK_ASSERT(font_sheet_texture.loadFromFile(get_texture_path(texture::font_sheet)), "Unable to load texture");
        first = false;
    }

    
    sf::Sprite B = cursive_font::get_letter('B');
    sf::Sprite u = cursive_font::get_letter('u');
    sf::Sprite l = cursive_font::get_letter('l');
    u.setPosition({ 75.0f, 0.0f });
    l.setPosition({ 75.0f * 2.0f, 0.0f });
    
    target.draw(B);
    target.draw(u);
    target.draw(l);
    return;

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