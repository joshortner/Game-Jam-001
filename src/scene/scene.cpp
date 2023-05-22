#include "scene.h"
#include "common.h"
#include "bullet_killer.h"
#include "application.h"

#include <cassert>

static const char *blur_fragment_shader_src = BK_SHADER(
// Two pass Gaussian Blur Shader
uniform bool horizontal;
uniform sampler2D texture;
uniform float width;
uniform float height; 

float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    vec3 result = texture2D(texture, gl_TexCoord[0].xy).rgb * weight[0]; // current fragment's contribution
    vec2 tex_offset = vec2(1.0 / width, 1.0 / height); // gets size of single texel

    if (horizontal) {
        for(int i = 1; i < 5; ++i) {
            result += texture2D(texture, gl_TexCoord[0].xy + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture2D(texture, gl_TexCoord[0].xy - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else {
        for (int i = 1; i < 5; ++i) {
            result += texture2D(texture, gl_TexCoord[0].xy + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture2D(texture, gl_TexCoord[0].xy - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    gl_FragColor = vec4(result, 1.0);
});

static const char *bloom_final_shader_src = BK_SHADER(
uniform sampler2D u_scene_texture;
uniform sampler2D u_bloom_texture;
void main()
{
    vec4 scene_pixel = texture2D(u_scene_texture, gl_TexCoord[0].xy);
    vec4 bloom_pixel = texture2D(u_bloom_texture, gl_TexCoord[0].xy);
    gl_FragColor = scene_pixel + bloom_pixel;
});

namespace bk
{
    scene::scene(const sf::Vector2u& dimensions) :
        m_game_state { .m_obj_mgr = object_mgr(*this) },
        state<scene_state>(scene_state::created),
        m_dimensions(dimensions)
    {
        BK_ASSERT(m_surface.create(dimensions, application::get_context_settings()), "Error creating surface");
        BK_ASSERT(m_bloom_surface.create(dimensions), "Error creating bloom surface");
        BK_ASSERT(m_scratch_surface.create(dimensions), "Error creating scratch surface");

        //m_shaders.m_bloom_final   = create_shader(shader::bloom_final);
        //m_shaders.m_gaussian_blur = create_shader(shader::gaussian_blur);

        set_view(sf::View((sf::Vector2f)dimensions / 2.f, (sf::Vector2f)dimensions));
    }

    scene::~scene()
    {
        // todo delete shaders
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

    void scene::do_post_processing()
    {
        do_bloom_pass();   
    }

    sf::Shader *scene::get_shader(shader s)
    {
        if (m_shader_table.find(s) == m_shader_table.end()) {
            m_shader_table[s] = new sf::Shader(create_shader(s));
        }
        return m_shader_table[s];
    }

    void scene::do_bloom_pass()
    {
        sf::Shader *p_bloom_final   = get_shader(shader::bloom_final);
        sf::Shader *p_gaussian_blur = get_shader(shader::gaussian_blur);

        // 1) Copy the bloom surface to scratch surface
        m_scratch_surface.clear();
        sf::Sprite copy_sprite(m_bloom_surface.getTexture());
        copy_sprite.setScale({ 1.0f, 1.0f, });
        m_scratch_surface.draw(copy_sprite);
        m_scratch_surface.display();

        // 2) Blur the light sources
        sf::Sprite blur_sprite(m_scratch_surface.getTexture());
        blur_sprite.setColor(sf::Color::Blue);
        blur_sprite.setScale({ 1.0f, 1.0f });
        p_gaussian_blur->setUniform("width", (float)blur_sprite.getTexture()->getSize().x);
        p_gaussian_blur->setUniform("height", (float)blur_sprite.getTexture()->getSize().y);
        p_gaussian_blur->setUniform("texture", m_scratch_surface.getTexture());
        
        for (int i = 0; i < 1; i++) {
            // Horizontal pass
            p_gaussian_blur->setUniform("horizontal", true);
            m_scratch_surface.draw(blur_sprite, p_gaussian_blur);
        
            // Vertical pass
            p_gaussian_blur->setUniform("horizontal", false);
            m_scratch_surface.draw(blur_sprite, p_gaussian_blur);
        }

        // 3) Additive blending
        sf::Sprite final_sprite(m_surface.getTexture());
        p_bloom_final->setUniform("u_scene_texture", m_surface.getTexture());
        p_bloom_final->setUniform("u_bloom_texture", m_scratch_surface.getTexture());
        p_bloom_final->setUniform("u_exposure", 1.0f);
        m_surface.draw(final_sprite, p_bloom_final);
    }
}