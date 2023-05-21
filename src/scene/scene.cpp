#include "scene.h"
#include "common.h"

#include <cassert>

namespace bk
{
    scene::scene(const sf::Vector2u& dimensions) :
        m_game_state { .m_obj_mgr = object_mgr(*this) },
        state<scene_state>(scene_state::created),
        m_dimensions(dimensions)
    {
        BK_ASSERT(m_surface.create(dimensions), "Error creating surface");
        BK_ASSERT(m_bloom_surface.create(dimensions), "Error creating bloom surface");
        BK_ASSERT(m_scratch_surface.create(dimensions), "Error creating scratch surface");
        set_view(sf::View((sf::Vector2f)dimensions / 2.f, (sf::Vector2f)dimensions));
    }

    scene::~scene()
    {   }

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

    const sf::View& scene::get_view() const
    {
        return m_view;
    }

    void scene::set_view(const sf::View& view) 
    {
        m_view = view;
        m_surface.setView(view);
        m_bloom_surface.setView(view);
        m_scratch_surface.setView(view);
    }

    void scene::update_objects(double dt)
    {
        m_game_state.m_obj_mgr.on_update(dt);
    }

    void scene::render_objects()
    {
        m_game_state.m_obj_mgr.on_render(m_surface, render_pass::draw);
        m_game_state.m_obj_mgr.on_render(m_bloom_surface, render_pass::bloom);
        m_surface.display();
        m_bloom_surface.display();
    }

    void scene::clear_surfaces()
    {
        m_surface.clear();
        m_bloom_surface.clear();
    }

    void scene::on_event(event e)
    {
        m_game_state.m_obj_mgr.on_event(e);
    }
}