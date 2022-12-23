#pragma once

#include "FunctionPreCacher.hpp"
#include "PreCacherContainer.hpp"

#include <cstdint>
#include <iostream>

namespace SimpleApp
{
    struct Vector2
    {
        float x = 0.f, y = 0.f;

        Vector2 operator+(const Vector2& rhs) const
        {
            return Vector2{ x + rhs.x, y + rhs.y };
        }
        Vector2 operator-(const Vector2& rhs) const
        {
            return Vector2{ x - rhs.x, y - rhs.y };
        }
        Vector2 operator*(const Vector2& rhs) const
        {
            return Vector2{ x * rhs.x, y * rhs.y };
        }
    };

    inline Vector2 f(int32_t x)
    {
        return Vector2{ (float)x, (float)x } * Vector2{ 1.0f, 2.0f };
    }

    int SaveMain();
}

inline std::ostream& operator<<(std::ostream& os, const SimpleApp::Vector2& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
