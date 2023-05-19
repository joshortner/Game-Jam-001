#pragma once

#include "object_npc.h"
#include "object_allocator.h"

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

    object_handle create_npc();

private:
    static const inline uint32_t MAX_NPCS = 100;

    scene& m_scene;

    struct {
        object_allocator<object_npc> m_allocator;
        std::vector<object_npc *> m_active_list;
    } m_npcs;
};

}