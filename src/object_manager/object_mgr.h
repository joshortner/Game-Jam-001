#pragma once

#include "object_npc.h"
#include "event.h"

#include <SFML/Graphics.hpp>
#include <stdint.h>

#include <vector>

namespace bk
{

class scene;

class object_mgr
{
public:
    object_mgr(scene& scene);
    ~object_mgr();
    
    void on_update(double dt);
    void on_render(sf::RenderTarget& target);
    void on_event(event e);

    void remove_object(object_itf* object);

    void get_object_type(std::vector<object_itf*>& vector, object_type type) const;

    template<typename T>
    void get_object_type(std::vector<T*>& vector) const;

    template<typename T, typename... Args>
    T *create(Args&&... args);

private:
    scene& m_scene;

    std::vector<object_itf*> m_stage_list;
    std::vector<object_itf *> m_active_list;
};

template<typename T, typename... Args>
T *object_mgr::create(Args&&... args)
{    
    static_assert(std::is_base_of<object_itf, T>::value);
    T* p_obj = new T(std::forward<Args>(args)...);
    m_stage_list.push_back(p_obj);
    return p_obj;
}

template<typename T>
void object_mgr::get_object_type(std::vector<T*>& vector) const
{
    static_assert(std::is_base_of<object_itf, T>::value);

    vector.clear();
    vector.reserve(m_active_list.size());
    const object_type type = T::Type;

    for (auto* active : m_active_list)
        if ((active->get_type() == type || active->get_type() == object_type::any) && active->active())
            vector.push_back(reinterpret_cast<T*>(active));

    vector.shrink_to_fit();
}

}