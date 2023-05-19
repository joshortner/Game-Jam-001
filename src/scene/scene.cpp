#include "scene.h"

namespace bk
{
    scene::scene(const sf::Vector2u& dimensions) :
        state<scene_state>(scene_state::created)
    {
        msurface.create(dimensions);
    }

    const sf::Texture& scene::get_texture() const
    {
        return msurface.getTexture();
    }
}