#pragma once

#include <SFML/Graphics.hpp>
#include "../utility/state.h"
#include "../utility/no_copy.h"

namespace bk
{
    enum class animation_state
    {
        waiting,
        running,
        done
    };

    class animation_node_itf :
        public utility::state<animation_state>,
        public utility::no_copy
    {
    public:
        animation_node_itf();
        virtual ~animation_node_itf() = default;

        void set_next_animation(animation_node_itf* next_animation);
        animation_node_itf* get_next_animation() const;

        void start();
        void stop();

        virtual double interpolate(const double& t) const = 0;
        virtual void   update() = 0;

    protected:
        sf::Clock m_timer;

    private:
        animation_node_itf* m_next_node;
    };
}