#pragma once

#include "object_itf.h"

#include <SFML/Graphics.hpp>

namespace bk
{

class scene;

class object_button : public object_itf
{
public:
    object_button(scene& scene);

    void on_update(double dt) override { } 
    void on_render(sf::RenderTarget& target) override { }
    void on_event(event e) override;

    virtual void on_click() { }
};

class object_button_mm_start : public object_button
{
public:
    object_button_mm_start(scene &scene);

    void on_render(sf::RenderTarget& target) override;
    virtual void on_click() override;

private:
    sf::Texture m_texture;
};

}