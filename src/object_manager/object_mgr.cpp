#include "object_mgr.h"

#define GET_AVAIL_OBJ_IDX_COMMON(_idx_var, _obj_count, _obj_buffer) \
    do { \
        for (int i = 0; i < _obj_count; i++) { \
            if (!_obj_buffer[i].m_active) { \
                _idx_var = i; \
                break; \
            } \
        } \
    } while (0)

namespace bk
{

object_mgr::object_mgr(scene& scene) : 
    m_scene(scene) 
{
    m_npcs.mp_allocator = new object_allocator<object_npc>(MAX_NPCS);
}

object_mgr::~object_mgr()
{
    for (object_npc* p_npc : m_npcs.m_active_list) { delete p_npc; }
    delete m_npcs.mp_allocator;
}

void object_mgr::on_update()
{
    for (object_npc* p_npc : m_npcs.m_active_list) { p_npc->on_update(); }
}

void object_mgr::on_render()
{
    for (object_npc* p_npc : m_npcs.m_active_list) { p_npc->on_render(); }
}

object_handle object_mgr::create_npc()
{
    return {
        .m_type = object_type::npc,
        .m_id   = (object_id)m_npcs.mp_allocator->allocate(m_scene)
    };
}

}