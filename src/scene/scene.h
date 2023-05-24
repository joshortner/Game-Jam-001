#pragma once

#include "state.h"
#include "no_copy.h"
#include "event.h"

#include "bullet_killer.h"

#include "../bullet_killer.h"
#include "../systems/system.h"

#include <unordered_map>
#include <flecs.h>
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
        sf::RenderTexture m_bloom_surface;
        sf::RenderTexture m_scratch_surface;

        std::unordered_map<shader, sf::Shader *> m_shader_table;

        std::vector<system*> m_systems;
        sf::View m_view;
        std::unordered_map<bk::texture, sf::Texture*> m_textures;
        const sf::Vector2u m_dimensions;

        flecs::world m_world; // container for all entities

    public:
        scene(const sf::Vector2u& dimensions);
        virtual ~scene();

        sf::Vector2u       get_size() const;
        const sf::Texture& get_texture() const;
        const sf::View&    get_view() const;
        void               set_view(const sf::View& view);

        sf::RenderTexture& get_render_texture() { return m_surface; }
        sf::Texture* get_texture(bk::texture texture);

        // Unsure if these are necissary
        void update_objects(double dt);
        void render_objects();
        void clear_surfaces();
        void do_post_processing();

        sf::Shader *get_shader(shader s);

        virtual void on_update(double dt) = 0;
        virtual void on_render() { };
        virtual void on_event(event e);

        // Systems
        const std::vector<system*>& get_systems() const { return m_systems; }
        template<typename T, typename... Args> 
        void add_system(Args&&... args)
        {
            m_systems.push_back(new T(args...));
        }

        flecs::world& get_world() { return m_world; }

    private:
        void do_bloom_pass();
    };
}