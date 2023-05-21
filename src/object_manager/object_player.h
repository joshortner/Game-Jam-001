#pragma once

#include <bitset>

#include "object_itf.h"
//#include "bullet_killer.h"

#include <flecs.h>

#include "components.h"

namespace bk
{
    class scene;

    class object_player :
        public component::scriptable_object,
        public component::input_object
    {
    public:
        object_player(scene& scene, flecs::world& world);

        void on_update(double dt, flecs::world& world) override;
        void on_event(bk::event event) override;

    private:
        flecs::entity m_player;
        std::bitset<5> m_input;
        scene& m_scene;
        sf::Clock clock;
    };

    /*
    class object_player :
        public object_itf
    {
    public:
        object_player(scene& scene, const sf::Texture& bullet);

        void on_update(double dt);
        void on_render(sf::RenderTarget& target, render_pass pass);
        void on_event(event e);

        void shoot(uint32_t bullet = 1) { if (bullets) bullets -= bullet; }
        uint32_t get_bullets() const { return bullets; }

        sf::Vector2f get_pos() const { return rect.getPosition(); }

        TYPE_ENUM(object_type::player);

    private:
        void draw_pass(sf::RenderTarget& target);

        sf::Sprite m_ammo;

        std::bitset<4> m_movement;
        const float K = 5.f;
        float m_max_vel = 1000.f;
        sf::Vector2f m_velocity;
        sf::Vector2f m_move_dir;
        sf::RectangleShape rect;

        float hp = 1.f;
        uint32_t bullets = 100;
    };  */
}