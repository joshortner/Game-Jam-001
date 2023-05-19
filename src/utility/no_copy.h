#pragma once

namespace bk::utility
{
    struct no_copy
    {
        no_copy() = default;
        no_copy(const no_copy&) = delete;
    };
}