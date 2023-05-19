#include "object_mgr.h"

namespace bk
{

object_mgr::object_mgr(scene& scene) : 
    m_scene(scene)
{   }

object_mgr::~object_mgr()
{
    for (auto* object : m_active_list) delete object;
    m_active_list.clear();
}

void object_mgr::on_update(double dt)
{
    for (object_itf* p_obj : m_active_list) { p_obj->on_update(dt); }
}

void object_mgr::on_render(sf::RenderTarget& target)
{
    std::sort(m_active_list.begin(), m_active_list.end(), [](auto* a, auto* b){ return a->get_z() > b->get_z(); });
    for (object_itf* p_obj : m_active_list) { p_obj->on_render(target); }
}

void object_mgr::on_event(event e)
{
    for (object_itf* p_obj : m_active_list) { p_obj->on_event(e); }
}

void object_mgr::get_object_type(std::vector<object_itf*>& vector, object_type type) const
{
    vector.clear();
    vector.reserve(m_active_list.size());

    std::copy_if(m_active_list.begin(), m_active_list.end(), std::back_inserter(vector), 
        [type](object_itf* object) {
            return type == object_type::any || object->get_type() == type;
        }
    );
}

}