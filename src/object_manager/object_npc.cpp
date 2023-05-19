#include "object_npc.h"

#include <stdio.h>

namespace bk
{

void object_npc::on_update(double dt) 
{

} 

void object_npc::on_render(const sf::RenderTarget& target) 
{
    
}

void object_npc::on_event(event e)
{
    printf("NPC Event: %d\n", e.m_type);
}

}