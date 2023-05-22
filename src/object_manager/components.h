#pragma once

#include "../event/event.h"
#include "../bullet_killer.h"
#include <SFML/Graphics.hpp>

namespace bk::component
{
    enum class player {};
    enum class enemy {};
    enum class bullet {};

    struct ammo
    {
        uint32_t count;
    };

    struct transform
    {
        struct 
        {
            float x, y;
        } position;

        struct 
        {
            float x, y;
        } scale;

        float rotation;
    };
    
    struct velocity
    {
        float x;
        float y;
    };

    struct hp
    {
        float value;
        float max;
        float offset;
    };

    struct force
    {
        float m;
        float x;
        float y;
        float k;
        float max_velocity;
    };

    struct sprite
    {
        sf::Texture* texture;
    };

    struct rectangle
    {
        float width;
        float height;
        sf::Color color;
    };

    struct bounding_box
    {
        float x;
        float y;
        float width;
        float height;
    };

    struct scriptable_object
    {
        virtual void on_render(sf::RenderTarget&, render_pass) { };
        virtual void on_update(double, flecs::world&) { };
    };

    struct input_object
    {
        virtual void on_event(bk::event event) = 0;
    };

    struct scriptable
    {
        scriptable_object* object;
    };

    struct input
    {
        input_object* object;
    };
}