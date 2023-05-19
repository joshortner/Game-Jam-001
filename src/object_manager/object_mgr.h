#pragma once

#include "object_npc.h"

#include <stdint.h>
#include <limits.h>

namespace bk
{

enum class object_type
{
    npc
};

struct object_handle
{
    object_type m_type;
    uint32_t m_id;
};

static inline const uint32_t invalid_object = UINT32_MAX;

class object_mgr
{
public:

    void on_update();
    void on_render();

    object_handle create_npc();

private:

    static const inline uint32_t MAX_NPCS = 100;

    object_npc m_npcs[MAX_NPCS];
    
};

}