#include "object_mgr.h"

namespace bk
{

object_mgr::object_mgr(scene& scene) : 
    m_scene(scene),
    m_npcs { object_allocator<object_npc>(MAX_NPCS) }
{   }

void object_mgr::on_update(double dt)
{
    for (object_npc* p_npc : m_npcs.m_active_list) { p_npc->on_update(dt); }
}

void object_mgr::on_render(const sf::RenderTarget& target)
{
    for (object_npc* p_npc : m_npcs.m_active_list) { p_npc->on_render(target); }
}

object_handle object_mgr::create_npc()
{
    return {
        .m_type = object_type::npc,
        .m_id   = (object_id)m_npcs.m_allocator.allocate(m_scene)
    };
}

}