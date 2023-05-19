#include "animation_system.h"

#include <iostream>

namespace bk
{
    void animation_system::push_animation(animation_node_itf* node)
    {
        m_nodes.push_back(node);
    }

    void animation_system::update()
    {
        for (animation_node_itf*& node : m_nodes)
        {
            if (node->get_state() == animation_state::waiting) node->start();

            node->update();

            if (node->get_state() == animation_state::done)
            {
                animation_node_itf* next_node = node->get_next_animation();
                delete node;
                node = next_node;
            }
        }

        std::vector<animation_node_itf*> no_nullptrs;
        no_nullptrs.reserve(m_nodes.size());
        std::copy_if(m_nodes.begin(), m_nodes.end(), std::back_inserter(no_nullptrs), 
            [](animation_node_itf* node) {
                return node != nullptr;
            }
        );

        m_nodes.resize(no_nullptrs.size());
        std::copy(no_nullptrs.begin(), no_nullptrs.end(), m_nodes.begin());
    }

    uint32_t animation_system::running_animations() const
    {
        return (uint32_t)m_nodes.size();
    }
}