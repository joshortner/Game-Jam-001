#include "object_mgr.h"

namespace bk
{

object_mgr::object_mgr(scene& scene) : 
    m_scene(scene)
{ 
    object_npc* p_obj = create<object_npc>(scene);
}

void object_mgr::on_update(double dt)
{
    for (object_itf* p_obj : m_active_list) { p_obj->on_update(dt); }
}

void object_mgr::on_render(const sf::RenderTarget& target)
{
    for (object_itf* p_obj : m_active_list) { p_obj->on_render(target); }
}

void object_mgr::on_event(event e)
{
    for (object_itf* p_obj : m_active_list) { p_obj->on_event(e); }
}

}