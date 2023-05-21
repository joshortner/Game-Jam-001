#pragma once

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

enum class texture
{
    start_button_on,
    start_button_off,
    main_menu_gun_0,
    room,
    bullet,
    numbers,
    person,
    letters
};

std::string get_texture_path(texture tex);

const char *get_asset_dir();

}