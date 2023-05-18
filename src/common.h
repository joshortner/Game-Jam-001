#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cassert>

#ifdef _WIN32
    #define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
    #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define BK_ASSERT(condition, message, ...)               \
    do                                                   \
    {                                                    \
        if (!(condition))                                \
        {                                                \
            printf("[BK ASSERT] %s:%d -- " message "\n", \
               __FILENAME__,                             \
               __LINE__,                                 \
               ##__VA_ARGS__);                           \
            assert(0);                                   \
        }                                                \
    } while(0);
