#include "bullet_killer.h"
#include "common.h"

#include <filesystem>

namespace bk
{

static inline const char * const g_texture_files_table[] = {
    "main_menu_start_on.png",
    "main_menu_start_off.png",
    "main_menu_border.png",
    "main_menu_gun_on.png",
    "main_menu_gun_off.png",
    "main_menu_title.png",
    "room.png",
    "bullet.png",
    "numbers.png",
    "person.png",
    "letters.png"
};

std::string get_texture_path(texture tex)
{
    std::filesystem::path texture_path(get_asset_dir()); 
    texture_path /= TEXTURE_DIR; 
    texture_path /= g_texture_files_table[(uint32_t)tex];
    return texture_path.string();
}

struct shader_table_entry 
{
    const char *mp_vert;
    const char *mp_frag;
};

static inline const shader_table_entry g_shader_table[] = {
    { nullptr, "gaussian_blur.frag" },
    { nullptr, "bloom_final.frag" }
};

sf::Shader create_shader(shader s)
{
    const char *p_vert_file = g_shader_table[(uint32_t)s].mp_vert;
    const char *p_frag_file = g_shader_table[(uint32_t)s].mp_frag;

    std::filesystem::path vertex_filepath(get_asset_dir()); 
    std::filesystem::path fragment_filepath(get_asset_dir()); 

    vertex_filepath   /= SHADER_DIR;
    fragment_filepath /= SHADER_DIR;

    if (p_vert_file != nullptr) { vertex_filepath /= p_vert_file; }
    if (p_frag_file != nullptr) { fragment_filepath /= p_frag_file; }

    sf::Shader shader;

    if (p_vert_file && p_frag_file) {
        BK_ASSERT(shader.loadFromFile(vertex_filepath, fragment_filepath), "Unable to load shader");;
    }
    else if (p_vert_file && !p_frag_file) {
        BK_ASSERT(shader.loadFromFile(vertex_filepath, sf::Shader::Vertex), "Unable to load shader");
    }
    else if (!p_vert_file && p_frag_file) {
        BK_ASSERT(shader.loadFromFile(fragment_filepath, sf::Shader::Fragment), "Unable to load shader");
    }
    else {
        BK_ASSERT(0, "Shader table nullptr entries");
    }

    return shader;
}

const char *get_asset_dir()
{
#ifdef BK_ASSET_DIR
    return BK_ASSET_DIR;
#else
    BK_ASSERT(0, "Asset dir undefined");
#endif
}

}