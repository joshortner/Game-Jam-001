#include "scene.h"

#include <cassert>

namespace bk
{
    scene::scene(const sf::Vector2u& dimensions) :
        state<scene_state>(scene_state::created)
    {
        assert(msurface.create(dimensions));
    }

    const sf::Texture& scene::get_texture() const
    {
        return msurface.getTexture();
    }
}