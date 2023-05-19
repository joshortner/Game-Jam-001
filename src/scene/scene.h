#pragma once

#include "state.h"
#include "no_copy.h"
#include "object_mgr.h"
#include "event.h"

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

    public:

        struct game_state
        {
            object_mgr m_obj_mgr;
        };

        // initializes the msurface member
        scene(const sf::Vector2u& dimensions);
        virtual ~scene() = default;

        sf::Vector2u       get_size() const;
        const sf::Texture& get_texture() const;
        game_state&        get_game_state();

        virtual void on_update(double dt) = 0;
        virtual void on_render() = 0;
        virtual void on_event(event e);

    private:
        const sf::Vector2u m_dimensions;
        game_state m_game_state;
    };
}