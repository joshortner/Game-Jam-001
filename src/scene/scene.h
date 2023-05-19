#pragma once

#include "../utility/state.h"
#include "../utility/no_copy.h"

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
        sf::RenderTexture msurface;

    public:
        // initializes the msurface member
        scene(const sf::Vector2u& dimensions);
        virtual ~scene() = default;

        const sf::Texture& get_texture() const;

        virtual void on_update(double dt) = 0;
        virtual void on_render() = 0;
    };
}