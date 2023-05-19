#pragma once

#include <cstdint>
#include <cassert>
#include <vector>

#include "node_interface.h"

namespace bk
{
    class animation_system
    {
    public:
        /*
        template<typename T, typename... Args>
        T* emplace_animation(Args... args)
        {
            static_assert(std::is_base_of<animation_node_itf, T>::value);
            m_nodes.push_back(new T(args...));
            m_nodes.back()->start();
            return (T*)m_nodes.back();
        }*/

        void push_animation(animation_node_itf* node);

        void     update();
        uint32_t running_animations() const;

    private:
        std::vector<animation_node_itf*> m_nodes;
    };
}