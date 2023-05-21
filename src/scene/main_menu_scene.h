#pragma once

#include "scene.h"
#include "hover_system.h"

#include <SFML/Graphics.hpp>

namespace bk
{

class main_menu_scene : 
    public scene
{
public:
    main_menu_scene(const sf::Vector2u& dimensions);

    virtual void on_update(double dt) override;
    virtual void on_render() override;
    virtual void do_post_processing() override;

private:
    hover_system m_hover_system;
    sf::Texture m_start_button_on;
    sf::Texture m_start_button_off;
    sf::Texture m_gun_0;
};

}