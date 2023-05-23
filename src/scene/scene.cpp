//#include "../object_manager/object_itf.h"
#include "../object_manager/components.h"
#include "scene.h"
#include "common.h"

#include <cassert>

namespace bk
{
    scene::scene(const sf::Vector2u& dimensions) :
        state<scene_state>(scene_state::created),
        m_dimensions(dimensions)
    {
        BK_ASSERT(m_surface.create(dimensions), "Error creating surface");
        set_view(sf::View((sf::Vector2f)dimensions / 2.f, (sf::Vector2f)dimensions));
    }

    scene::~scene()
    {   
        for (auto it = m_textures.begin(); it != m_textures.end(); it++)
            delete (*it).second;

        for (auto* system : m_systems) delete system;
    }

    sf::Vector2u scene::get_size() const
    {
        return m_dimensions;
    }

    const sf::Texture& scene::get_texture() const
    {
        return m_surface.getTexture();
    }

    /*
    scene::game_state& scene::get_game_state()
    {
        return m_game_state;
    }*/

    const sf::View& scene::get_view() const
    {
        return m_view;
    }

    void scene::set_view(const sf::View& view) 
    {
        m_view = view;
        m_surface.setView(view);
    }
    
    sf::Texture* scene::get_texture(bk::texture texture)
    {
        auto tex = m_textures.find(texture);
        if (tex != m_textures.end())
            return (*tex).second;
        else
        {
            sf::Texture* _texture = new sf::Texture();
            _texture->loadFromFile(get_texture_path(texture));
            m_textures.insert(std::pair<bk::texture, sf::Texture*>(texture, _texture));
            return _texture;
        }
    }

    void scene::update_objects(double dt)
    {
        //m_game_state.m_obj_mgr.on_update(dt);
    }

    void scene::render_objects()
    {
        using namespace component;

        m_surface.clear();
        
        // inside each render 
        // search for child of current entity and 
        // then do a render using an offset given the entity's 
        // transform
        
        auto sprites = m_world.filter<sprite, transform>();
        sprites.each([this](sprite& sprite, transform& transform) 
        {
            sf::Sprite object(*sprite.texture);
            object.setPosition(sf::Vector2f(transform.position.x, transform.position.y));
            object.setScale(sf::Vector2f(transform.scale.x, transform.scale.y));
            object.setRotation(sf::radians(transform.rotation));
            this->m_surface.draw(object);
        });

        auto rectangles = m_world.filter<rectangle, transform>();
        rectangles.each([this](rectangle& rect, transform& transform)
        {
            sf::RectangleShape sf_rect;
            sf_rect.setSize(sf::Vector2f(rect.width, rect.height));
            sf_rect.setOrigin(sf::Vector2f(sf_rect.getSize().x / 2.f, sf_rect.getSize().y / 2.f));
            sf_rect.setFillColor(rect.color);
            sf_rect.setPosition(sf::Vector2f(transform.position.x, transform.position.y));
            sf_rect.setScale(sf::Vector2f(transform.scale.x, transform.scale.y));
            sf_rect.setRotation(sf::radians(transform.rotation));
            this->m_surface.draw(sf_rect);
        });

        auto scriptable = get_world().filter<component::scriptable>();
        scriptable.each([this](component::scriptable& script)
        { script.object->on_render(this->m_surface, render_pass::draw); });

        /*
        const char *shader_src = BK_SHADER(
        void main()
        {
            int var = 0;
        });

        sf::Shader shader;
        BK_ASSERT(shader.loadFromMemory(shader_src, sf::Shader::Fragment), "Unable to load shader");
        */

        //m_game_state.m_obj_mgr.on_render(m_surface, render_pass::draw);

        m_surface.display();
    }

    void scene::on_event(event e)
    {
        //m_game_state.m_obj_mgr.on_event(e);
    }
}