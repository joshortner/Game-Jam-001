#pragma once

#include "state.h"
#include "no_copy.h"
#include "event.h"
#include "object_mgr.h"

#include <SFML/Graphics.hpp>

namespace bk
{
    enum class scene_state
    {
        created,
        initialized,
        running,
        complete
    };

    class scene :
        public utility::no_copy,
        public utility::state<scene_state>
    {
    protected:
        sf::RenderTexture m_surface;
        sf::View m_view;

    public:
        struct game_state
        {
        // Managers
            object_mgr m_obj_mgr;
        };

        // initializes the msurface member
        scene(const sf::Vector2u& dimensions);
        virtual ~scene();

        sf::Vector2u       get_size() const;
        const sf::Texture& get_texture() const;
        game_state&        get_game_state();
        const sf::View&    get_view() const;
        void               set_view(const sf::View& view);

        void update_objects(double dt);
        void render_objects();

        virtual void on_update(double dt) = 0;
        virtual void on_render() { };
        virtual void on_event(event e);

        object_mgr& get_object_manager() { return m_game_state.m_obj_mgr; }

    private:
        const sf::Vector2u m_dimensions;

    protected:
        game_state m_game_state;
    };
}