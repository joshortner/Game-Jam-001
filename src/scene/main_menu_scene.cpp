#include "main_menu_scene.h"
#include "object_button.h"
#include "bullet_killer.h"
#include "common.h"

#include <SFML/Graphics.hpp>

namespace bk
{

main_menu_scene::main_menu_scene(const sf::Vector2u& dimensions) :
    scene(dimensions), m_hover_system(*this)
{
// Load Resources
    BK_ASSERT(m_start_button_on.loadFromFile(get_texture_path(texture::start_button_on)), "Unable to load texture");
    BK_ASSERT(m_start_button_off.loadFromFile(get_texture_path(texture::start_button_off)), "Unable to load texture");
    BK_ASSERT(m_gun_0.loadFromFile(get_texture_path(texture::main_menu_gun_0)), "Unable to load texture");

// Create objects
    object_button_mm_start *p_start_button = m_game_state.m_obj_mgr.create<object_button_mm_start>(
        *this, &m_start_button_on, & m_start_button_off);
}

void main_menu_scene::on_update(double dt) 
{
    // Systems
    m_hover_system.on_update(dt);
}

void main_menu_scene::on_render() 
{
    sf::Sprite gun_sprite(m_gun_0);
    m_surface.draw(gun_sprite);
}

void main_menu_scene::do_post_processing() 
{
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

    sf::Shader blur_shader;
    sf::Shader final_bloom_shader;
    BK_ASSERT(blur_shader.loadFromMemory(blur_fragment_shader_src, sf::Shader::Fragment), "Unable to load shader");
    BK_ASSERT(final_bloom_shader.loadFromMemory(bloom_final_shader_src, sf::Shader::Fragment), "Unable to load shader");

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
    blur_shader.setUniform("width", (float)blur_sprite.getTexture()->getSize().x);
    blur_shader.setUniform("height", (float)blur_sprite.getTexture()->getSize().y);
    blur_shader.setUniform("texture", m_scratch_surface.getTexture());
    
    for (int i = 0; i < 200; i++) {
        // Horizontal pass
        blur_shader.setUniform("horizontal", true);
        m_scratch_surface.draw(blur_sprite, &blur_shader);
    
        // Vertical pass
        blur_shader.setUniform("horizontal", false);
        m_scratch_surface.draw(blur_sprite, &blur_shader);
    }

    // 3) Additive blending
    sf::Sprite final_sprite(m_surface.getTexture());
    final_bloom_shader.setUniform("u_scene_texture", m_surface.getTexture());
    final_bloom_shader.setUniform("u_bloom_texture", m_scratch_surface.getTexture());
    m_surface.draw(final_sprite, &final_bloom_shader);

    // Temp render image
    //sf::Sprite tmp_sprite(m_scratch_surface.getTexture());
    //tmp_sprite.setScale({ 0.75f, 0.75f });
    //m_surface.draw(tmp_sprite);
}

}