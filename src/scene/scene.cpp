#include "scene.h"

#include <cassert>

namespace bk
{
    scene::scene(const sf::Vector2u& dimensions) :
        state<scene_state>(scene_state::created),
        m_dimensions(dimensions)
    {
        assert(m_surface.create(dimensions));
        m_game_state.mp_obj_mgr = new object_mgr(*this);
    }

    sf::Vector2u scene::get_size() const
    {
        return m_dimensions;
    }

    const sf::Texture& scene::get_texture() const
    {
        return m_surface.getTexture();
    }

    scene::game_state& scene::get_game_state()
    {
        return m_game_state;
    }
}