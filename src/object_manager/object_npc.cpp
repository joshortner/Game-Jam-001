#include "object_npc.h"


#include <iostream>
#include <stdio.h>

namespace bk
{
    object_npc::object_npc(scene& scene) :
        object_itf(scene, object_type::npc)
    {
        m_rect.setFillColor(sf::Color::Blue);
        //m_rect.setOrigin({ m_rect.getSize().x / 2.f, m_rect.getSize().y / 2.f });
        
        m_position = { 100, 100 };
        m_scale = { 20, 20 };
    }

    void object_npc::on_update(double dt) 
    {
        
    } 

    void object_npc::on_render(sf::RenderTarget& target, render_pass pass) 
    {
        switch (pass)
        {
            case render_pass::draw:
            {
                m_rect.setSize(m_scale);
                m_rect.setPosition(m_position);
                target.draw(m_rect);
                break;
            }
        }
    }

    void object_npc::on_event(event e)
    {
        
    }

}