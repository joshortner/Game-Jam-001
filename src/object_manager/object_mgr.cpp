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

void object_mgr::on_update()
{
    for (int i = 0; i < MAX_NPCS; i++) {
        if (m_npcs[i].m_active) {
            m_npcs[i].on_update();
        }
    }
}

void object_mgr::on_render()
{
    for (int i = 0; i < MAX_NPCS; i++) {
        if (m_npcs[i].m_active) {
            m_npcs[i].on_render();
        }
    }
}

object_handle object_mgr::create_npc()
{
    int obj_idx = -1;
    GET_AVAIL_OBJ_IDX_COMMON(obj_idx, MAX_NPCS, m_npcs);
    
    object_handle handle = {
        .m_type = object_type::npc,
        .m_id   = invalid_object
    };
    
    if (obj_idx != -1) {
        handle.m_id = obj_idx;
        m_npcs[obj_idx].m_active = true;
    }

    return handle;
}

}