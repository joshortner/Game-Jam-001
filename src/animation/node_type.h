#pragma once

#include "node_interface.h"

namespace bk
{
    template<typename T>
    class animation :
        public animation_node_itf
    {
    public:
        animation(T* const value, const T& start_value, const T& end_value, const double& duration, const double& delay = 0.0);
        virtual ~animation() = default;

        double get_delay() const;
        double get_duration() const;
        
        T get_start_value() const;
        T get_end_value() const;

        void update() override;

    private:
        const T m_start_value;
        const T m_end_value;
        const double m_duration;
        const double m_delay;

    protected:
        T* const m_value;
    };

    template<typename T>
    animation<T>::animation(T* const value, const T& start_value, const T& end_value, const double& duration, const double& delay) :
        m_value(value),
        m_start_value(start_value),
        m_end_value(end_value),
        m_duration(duration),
        m_delay(delay)
    {   }

    template<typename T>
    double animation<T>::get_delay() const
    {
        return m_delay;
    }

    template<typename T>
    double animation<T>::get_duration() const
    {
        return m_duration;
    }

    template<typename T>
    T animation<T>::get_start_value() const
    {
        return m_start_value;
    }

    template<typename T>
    T animation<T>::get_end_value() const
    {
        return m_end_value;
    }

    template<typename T>
    void animation<T>::update() 
    {
        const double relative_time = (m_timer.getElapsedTime().asSeconds() - m_delay) / m_duration;

        if (get_state() == animation_state::running && relative_time > 0)
        {
            *m_value = m_start_value + (m_end_value - m_start_value) * interpolate(relative_time);

            if (relative_time >= 1)
            {
                *m_value = m_end_value;
                stop();
            }
        }
    }
}