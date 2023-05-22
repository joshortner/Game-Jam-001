#pragma once

#include "object_itf.h"
#include "bullet_killer.h"

#include <SFML/Graphics.hpp>

namespace bk
{

class scene;

class object_button : public object_itf
{
public:

    object_button(scene& scene);

    //void on_render(sf::RenderTarget& target, render_pass pass) override { }
    void on_event(event e) override;
    //virtual sf::FloatRect get_bounding_box() const override { return sf::FloatRect(m_position, m_scale); }

    virtual void on_click() { }
};

class object_button_mm_start : public object_button
{
public:

    object_button_mm_start(
        scene &scene,
        sf::Texture *p_on,
        sf::Texture *p_off
    );

    virtual void on_render(sf::RenderTarget& target, render_pass pass) override;
    virtual void on_update(double dt) override;
    virtual sf::FloatRect get_bounding_box() const override; 
    virtual void on_click() override;

private:
    sf::Texture *mp_button_on;
    sf::Texture *mp_button_off;
    bool m_on; 
};

}