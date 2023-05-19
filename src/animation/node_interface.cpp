#include "node_interface.h"

namespace bk
{
    animation_node_itf::animation_node_itf() :
        m_next_node(nullptr),
        utility::state<animation_state>(animation_state::waiting)
    {   }

    void animation_node_itf::set_next_animation(animation_node_itf* next_animation)
    {
        m_next_node = next_animation;
    }

    animation_node_itf* animation_node_itf::get_next_animation() const
    {
        return m_next_node;
    }

    void animation_node_itf::start() 
    {
        set_state(animation_state::running);
        m_timer.restart();
    }

    void animation_node_itf::stop()
    {
        set_state(animation_state::done);
    }
}