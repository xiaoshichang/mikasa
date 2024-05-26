#pragma once
#include <limits>
#include <cmath>
#include <cfloat>

namespace mikasa::Runtime::Foundation
{
    constexpr float PI = 3.14159265358979323846f;
    constexpr float TWO_PI = PI * 2;

    template <typename T>
    struct comparison_traits
    {
        static bool equal(const T& a, const T& b)
        {
            return a == b;
        }
    };

    template<>
    struct comparison_traits<float>
    {
        static bool equal(const float& a, const float& b)
        {
            return fabs(a - b) < FLT_EPSILON;
        }
    };

    template<>
    struct comparison_traits<double>
    {
        static bool equal(const double& a, const double& b)
        {
            return fabs(a - b) < DBL_EPSILON;
        }
    };
}



