#pragma once

#include "SFML/Graphics.hpp"

namespace bk
{

class object_mgr;

class object_itf
{
public:

    object_itf() : m_active(false) { }

    virtual void on_update() = 0;
    virtual void on_render() = 0;

protected:

    bool m_active;
    sf::Transform m_transform;

    friend class object_mgr;
};

}