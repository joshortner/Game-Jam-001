#pragma once

#include "SFML/Window.hpp"

namespace bk
{

enum class event_type
{
    unknown,
    close,
    key_press,
    key_release,
    mouse_button_pressed,
    mouse_button_released,
    mouse_moved
};

struct event
{
    event_type m_type;
    union {
        sf::Event::KeyEvent m_key;
        sf::Event::MouseButtonEvent m_mouse_button;
        sf::Event::MouseMoveEvent m_mouse_move;
    };
};

}