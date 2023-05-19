#pragma once

#include "object_itf.h"

namespace bk
{

class scene;

class object_npc : public object_itf
{
public:

    object_npc(scene& scene) : object_itf(scene) { }

    virtual void on_update(double dt) override;   
    virtual void on_render(const sf::RenderTarget& target) override;
    virtual void on_event(event e) override;

private:

};

}