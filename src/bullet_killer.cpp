#include "bullet_killer.h"
#include "common.h"

namespace bk
{

const char *get_asset_dir()
{
#ifdef BK_ASSET_DIR
    return BK_ASSET_DIR;
#else
    BK_ASSERT(0, "Asset dir undefined");
#endif
}

}