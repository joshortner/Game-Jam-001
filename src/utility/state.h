#pragma once

#include <iostream>

namespace bk::utility
{
    template<typename _state_enum>
    class state
    {
        _state_enum mstate;
    protected:
        void set_state(const _state_enum& new_state);

        virtual void on_state_changed(const _state_enum& new_state) { }

    public:
        state(const _state_enum& initial_state = 0);

        _state_enum get_state() const;
    };

    template<typename _state_enum>
    void state<_state_enum>::set_state(const _state_enum& new_state)
    {
        this->on_state_changed(new_state);
        mstate = new_state;
    }

    template<typename _state_enum>
    state<_state_enum>::state(const _state_enum& initial_state) :
        mstate(initial_state)
    {   }

    template<typename _state_enum>
    _state_enum state<_state_enum>::get_state() const
    {
        return mstate;
    }
}