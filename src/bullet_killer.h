#pragma once

#include <SFML/Graphics.hpp>

#include <string>

#define BK_SHADER(EXP) #EXP 

namespace bk
{

enum class render_pass
{
    draw,
    bloom
};

static inline const char * TEXTURE_DIR = "textures";
static inline const char * SHADER_DIR  = "shaders";

enum class texture
{
    start_button_on,
    start_button_off,
    main_menu_border,
    main_menu_gun_on,
    main_menu_gun_off,
    main_menu_title,
    room,
    bullet,
    numbers,
    person,
    letters
};

enum class shader
{
    gaussian_blur,
    bloom_final
};

std::string get_texture_path(texture tex);
sf::Shader create_shader(shader s);

const char *get_asset_dir();

}