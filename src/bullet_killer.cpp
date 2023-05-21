#include "bullet_killer.h"
#include "common.h"

#include <filesystem>

namespace bk
{

static inline const char * const g_texture_files_table[] = {
    "main_menu_start_on.png",
    "main_menu_start_off.png",
    "main_menu_gun_0.png",
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

const char *get_asset_dir()
{
#ifdef BK_ASSET_DIR
    return BK_ASSET_DIR;
#else
    BK_ASSERT(0, "Asset dir undefined");
#endif
}

}