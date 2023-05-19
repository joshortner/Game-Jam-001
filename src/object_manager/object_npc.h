#pragma once

#include "object_itf.h"

namespace bk
{

class scene;

class object_npc : public object_itf
{
public:
    object_npc(scene& scene);

    void on_update(double dt) override;   
    void on_render(sf::RenderTarget& target) override;
    void on_event(event e) override;

private:
    sf::RectangleShape m_rect;
};

}