#pragma once
#include "Commom.h"
#include "Runtime/Foundation/Assert.h"
#include "Runtime/Foundation/HAL/Memory/MAllocBase.h"


namespace mikasa::Runtime::Foundation
{
    template<typename T>
    struct Vector4 : public MallocOperation
    {
        // if T is is_floating_point, PrecisionType is T,
        // else PrecisionType is float
        typedef typename std::conditional<std::is_floating_point<T>::value, T, float>::type PrecisionType;

        union
        {
            T data[4];
            struct { T x, y, z, w; };
            struct { T r, g, b, a; };
        };

        Vector4<T>() : x(0), y(0), z(0), w(0) {};
        Vector4<T>(const Vector4<T>& v) = default;
        explicit Vector4<T>(const T& v) : x(v), y(v), z(v), w(v) {};
        Vector4<T>(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {};

        T& operator[](int idx)
        {
            MIKASA_ASSERT(idx < 4);
            return data[idx];
        }

        explicit operator const T*() const
        {
            return data;
        }

        inline bool operator==(const Vector4<T>& rhs) const noexcept
        {
            return comparison_traits<T>::equal(x, rhs.x)
                   && comparison_traits<T>::equal(y, rhs.y)
                   && comparison_traits<T>::equal(z, rhs.z)
                   && comparison_traits<T>::equal(w, rhs.w);
        }

        inline bool operator!=(const Vector4<T>& rhs) const noexcept
        {
            return !comparison_traits<T>::equal(x, rhs.x)
                   || !comparison_traits<T>::equal(y, rhs.y)
                   || !comparison_traits<T>::equal(z, rhs.z)
                   || !comparison_traits<T>::equal(w, rhs.w);
        }

        inline Vector4<T> operator+(const Vector4<T>& rhs) const noexcept
        {
            return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
        }

        inline Vector4<T> operator-(const Vector4<T>& rhs) const noexcept
        {
            return Vector4<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
        }

        inline Vector4<T> operator*(T scale)  const noexcept
        {
            return Vector4<T>(x * scale, y * scale, z * scale, w * scale);
        }

        inline Vector4<T> operator*(const Vector4<T>& rhs)  const noexcept
        {
            return Vector4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
        }

        friend inline Vector4<T> operator*(T scale, const Vector4<T>& rhs) noexcept
        {
            return Vector4<T>(rhs.x * scale, rhs.y * scale, rhs.z * scale, rhs.w * scale);
        }

        inline PrecisionType Dot(const Vector4<T>& rhs) const noexcept
        {
            PrecisionType result = 0;
            result += x * rhs.x;
            result += y * rhs.y;
            result += z * rhs.z;
            result += w * rhs.w;
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

        inline Vector4<T> Normalized() const noexcept
        {
            PrecisionType length = Length();
            if (length > 0)
            {
                length = 1.0 / length;
            }
            return *this * length;

        }

        inline void NormalizedInPlace() noexcept
        {
            PrecisionType length = Length();
            if (length > 0)
            {
                length = 1.0 / length;
            }
            x = x * length;
            y = y * length;
            z = z * length;
            w = w * length;
        }
    };

    typedef Vector4<int> Vector4i;
    typedef Vector4<float> Vector4f;
    typedef Vector4<double> Vector4d;
}


