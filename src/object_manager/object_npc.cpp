#include "object_npc.h"

#include <stdio.h>

namespace bk
{
    object_npc::object_npc(scene& scene) :
        object_itf(scene)
    {
        m_rect.setFillColor(sf::Color::Red);
        m_rect.setSize({ 20, 20 });
        m_rect.setOrigin({ m_rect.getSize().x / 2.f, m_rect.getSize().y / 2.f });
    }

    void object_npc::on_update(double dt) 
    {
        
    } 

    void object_npc::on_render(sf::RenderTarget& target) 
    {
        target.draw(m_rect);
    }

    void object_npc::on_event(event e)
    {
        
    }

}