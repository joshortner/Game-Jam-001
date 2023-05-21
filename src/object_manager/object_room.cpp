#include "object_room.h"

#include "../bullet_killer.h"

#include <iostream>

namespace bk
{
    object_room::object_room(scene& scene, sf::Vector2i coordinates) :
        object_itf(scene, object_type::room),
        m_coordinates(coordinates)
    {   
        if (!room_texture.loadFromFile(get_texture_path(texture::room)))
            std::cout << "Room texture failed to load\n";

        m_position = sf::Vector2f(
            (float)room_texture.getSize().x * coordinates.x,
            (float)room_texture.getSize().y * coordinates.y
        );
    }

    void object_room::on_update(double dt)
    {
        
    }

    void object_room::on_render(sf::RenderTarget& target, render_pass pass)
    {
        switch (pass)
        {
            case render_pass::draw:
            {
                sf::Sprite sprite(room_texture);
                sprite.setPosition(m_position);
                target.draw(sprite);  
                break;
            }
        }
    }

    void object_room::on_event(event e)
    {

    }
}