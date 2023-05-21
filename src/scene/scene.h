#pragma once

#include "state.h"
#include "no_copy.h"
#include "event.h"
//#include "object_mgr.h"

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
        sf::View m_view;

        flecs::world m_world; // container for all entities

    public:
    /*
        struct game_state
        {
        // Managers
            object_mgr m_obj_mgr;
        };*/

        // initializes the msurface member
        scene(const sf::Vector2u& dimensions);
        virtual ~scene();

        sf::Vector2u       get_size() const;
        const sf::Texture& get_texture() const;
        //game_state&        get_game_state();
        const sf::View&    get_view() const;
        void               set_view(const sf::View& view);

        sf::RenderTexture& get_render_texture() { return m_surface; }
        sf::Texture* get_texture(bk::texture texture);

        // Unsure if these are necissary
        void update_objects(double dt);
        void render_objects();

        virtual void on_update(double dt) = 0;
        virtual void on_render() { };
        virtual void on_event(event e);

        // Objects
        const std::vector<object_itf*>& get_objects() const { return m_objects; }
        template<typename T, typename... Args>
        void add_object(Args&... args)
        {
            static_assert(std::is_base_of<object_itf, T>::value);
            m_objects.push_back(new T(args...));
        }

        // Systems
        const std::vector<system*>& get_systems() const { return m_systems; }
        template<typename T> 
        void add_system()
        {
            m_systems.push_back(new T());
        }

        flecs::world& get_world() { return m_world; }
        //object_mgr& get_object_manager() { return m_game_state.m_obj_mgr; }

    private:
        std::unordered_map<bk::texture, sf::Texture*> m_textures;
        std::vector<system*> m_systems;
        std::vector<object_itf*> m_objects;
        const sf::Vector2u m_dimensions;

    //protected:
        //game_state m_game_state;
    };
}