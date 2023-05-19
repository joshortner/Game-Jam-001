#pragma once

#include "./scene/scene.h"
#include "./application/application.h"

#include <string>

namespace bk
{

static inline const char * TEXTURE_DIR = "textures";

enum class texture
{
    container,
    start_button
};

std::string get_texture_path(texture tex);

const char *get_asset_dir();

}