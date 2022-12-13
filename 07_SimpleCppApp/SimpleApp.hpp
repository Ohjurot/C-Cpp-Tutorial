#pragma once

#include "FunctionPreCacher.hpp"
#include "PreCacherContainer.hpp"

#include <cstdint>
#include <iostream>

namespace SimpleApp
{
    inline int32_t f(int32_t x)
    {
        return x * x + 5 * x + 5;
    }

    int SaveMain();
}
