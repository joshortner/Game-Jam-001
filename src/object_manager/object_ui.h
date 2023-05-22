#pragma once

#include "object_itf.h"

namespace bk
{

class scene;

class object_ui : public object_itf
{
public:

    object_ui(scene& scene) : object_itf(scene, object_type::ui) { }
};

class object_ui_mm_gun : public object_ui
{
public:

    object_ui_mm_gun(scene& scene) : object_ui(scene) { }

    virtual void on_render(sf::RenderTarget& target, render_pass pass) override;
    virtual void on_update(double dt) override;
    virtual void on_event(event e) override;

private:
    bool m_gun_anim_trigger = false;
};

}