#include "object_mgr.h"

namespace bk
{

object_mgr::object_mgr(scene& scene) : 
    m_scene(scene)
{ 
    
}

void object_mgr::on_update(double dt)
{
    for (object_itf* p_obj : m_active_list) { p_obj->on_update(dt); }
}

void object_mgr::on_render(sf::RenderTarget& target)
{
    for (object_itf* p_obj : m_active_list) { p_obj->on_render(target); }
}

void object_mgr::on_event(event e)
{
    for (object_itf* p_obj : m_active_list) { p_obj->on_event(e); }
}

void object_mgr::get_object_type(std::vector<object_itf*>& vector, object_type type) const
{
    std::copy_if(m_active_list.begin(), m_active_list.end(), std::back_inserter(vector), 
        [type](object_itf* object) {
            return object->get_type() == type;
        }
    );
}

}