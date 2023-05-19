#include "object_room.h"

#include "../bullet_killer.h"

namespace bk
{
    object_room::object_room(scene& scene) :
        object_itf(scene, object_type::room)
    {   
        if (!room_texture.loadFromFile(get_texture_path(texture::room)))
            std::cout << "Room texture failed to load\n";
    }

    void object_room::on_update(double dt)
    {
        
    }

    void object_room::on_render(sf::RenderTarget& target)
    {
        sf::Sprite sprite(room_texture);
        target.draw(sprite);
    }

    void object_room::on_event(event e)
    {

    }
}