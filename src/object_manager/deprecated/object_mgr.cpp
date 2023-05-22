#include "object_mgr.h"

#include <iostream>

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
    std::vector<object_itf*> temp;
    temp.reserve(m_active_list.size());

    // for some reason there are null objects here
    for (object_itf* p_obj : m_active_list) 
    { 
        if (p_obj->active()) 
        {
            p_obj->on_update(dt); 
            temp.push_back(p_obj);
        }
        else delete p_obj;
    }

    // copy temp list
    m_active_list.resize(temp.size());
    std::copy(temp.begin(), temp.end(), m_active_list.begin());

    // copy staged list over and clear it
    std::copy(m_stage_list.begin(), m_stage_list.end(), std::back_inserter(m_active_list));
    m_stage_list.clear();
}

void object_mgr::on_render(sf::RenderTarget& target, render_pass pass)
{
    std::sort(m_active_list.begin(), m_active_list.end(), [](auto* a, auto* b){ return a->get_z() > b->get_z(); });
    for (object_itf* p_obj : m_active_list) { p_obj->on_render(target, pass); }
}

void object_mgr::on_event(event e)
{
    for (object_itf* p_obj : m_active_list) { p_obj->on_event(e); }
}

void object_mgr::remove_object(object_itf* object)
{
    auto it = std::find(m_active_list.begin(), m_active_list.end(), object);
    assert(it != m_active_list.end());
    (*it)->set_active(false);
}

void object_mgr::get_object_type(std::vector<object_itf*>& vector, object_type type) const
{
    vector.clear();
    vector.reserve(m_active_list.size());

    std::copy_if(m_active_list.begin(), m_active_list.end(), std::back_inserter(vector), 
        [type](object_itf* object) {
            return (type == object_type::any || object->get_type() == type) && object->active();
        }
    );

    vector.shrink_to_fit();
}

}
