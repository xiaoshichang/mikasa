#pragma once
#include <type_traits>
#include "Commom.h"
#include "Runtime/Foundation/Assert.h"
#include "Runtime/Foundation/HAL/Memory/MAllocBase.h"


namespace mikasa::Runtime::Foundation
{
    template<typename T>
    struct Vector2 : public MallocOperation
    {
        typedef typename std::conditional<std::is_floating_point<T>::value, T, float>::type PrecisionType;

        union
        {
            T data[2];
            struct { T x, y; };
            struct { T Width, Height; };
            struct { T u, v; };
        };

        Vector2<T>() : x(0), y(0) {};
        Vector2<T>(const Vector2<T>& v) = default;
        Vector2<T>(const T& v) : x(v), y(v) {};
        Vector2<T>(const T& x, const T& y) : x(x), y(y) {};

        T& operator[](int idx)
        {
            MIKASA_ASSERT(idx < 2);
            return data[idx];
        }

        inline bool operator==(const Vector2<T>& rhs) const noexcept
        {
            return comparison_traits<T>::equal(x, rhs.x)
                   && comparison_traits<T>::equal(y, rhs.y);
        }

        inline bool operator!=(const Vector2<T>& rhs) const noexcept
        {
            return !comparison_traits<T>::equal(x, rhs.x)
                   || !comparison_traits<T>::equal(y, rhs.y);
        }

        inline Vector2<T> operator+(const Vector2<T>& rhs) const noexcept
        {
            return Vector2<T>(x + rhs.x, y + rhs.y);
        }

        inline Vector2<T> operator-(const Vector2<T>& rhs) const noexcept
        {
            return Vector2<T>(x - rhs.x, y - rhs.y);
        }

        inline Vector2<T> operator*(T scale)  const noexcept
        {
            return Vector2<T>(x * scale, y * scale);
        }

        inline PrecisionType Dot(const Vector2<T>& rhs) const noexcept
        {
            PrecisionType result = 0;
            result += x * rhs.x;
            result += y * rhs.y;
            return result;
        }

        inline PrecisionType Length() const noexcept
        {
            PrecisionType result = LengthSQ();
            return sqrtf(result);
        }

        inline PrecisionType LengthSQ() const noexcept
        {
            return Dot(*this);
        }

        inline Vector2<T> Normalized() const noexcept
        {
            PrecisionType length = Length();
            if (length > 0)
            {
                length = 1.0f / length;
            }
            return *this * length;
        }

        inline void NormalizedInPlace() noexcept
        {
            PrecisionType length = Length();
            if (length > 0)
            {
                length = 1.0f / length;
            }
            x = x * length;
            y = y * length;
        }
    };

    typedef Vector2<int> Vector2i;
    typedef Vector2<float> Vector2f;
    typedef Vector2<double> Vector2d;
}


