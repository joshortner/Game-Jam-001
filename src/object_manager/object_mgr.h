#pragma once

#include "object_npc.h"
#include "event.h"

#include <SFML/Graphics.hpp>
#include <stdint.h>

#include <vector>

namespace bk
{

class scene;

enum class object_type
{
    npc
};

typedef void * object_id;

struct object_handle
{
    object_type m_type;
    object_id m_id;
};

static inline const object_id invalid_object = nullptr;

class object_mgr
{
public:
    object_mgr(scene& scene);
    ~object_mgr() = default;
    void on_update(double dt);
    void on_render(const sf::RenderTarget& target);
    void on_event(event e);

    template<typename T, typename... Args>
    T *create(Args&&... args);

private:
    scene& m_scene;

    std::vector<object_itf *> m_active_list;
};

template<typename T, typename... Args>
T *object_mgr::create(Args&&... args)
{    
    T* p_obj = new T(std::forward<Args>(args)...);
    m_active_list.push_back(p_obj);
    return p_obj;
}

}