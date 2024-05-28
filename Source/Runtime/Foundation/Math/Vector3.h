#pragma once
#include "Commom.h"
#include "Runtime/Foundation/Assert.h"
#include "Runtime/Foundation/HAL/Memory/MAllocBase.h"


namespace mikasa::Runtime::Foundation
{
    template<typename T>
    struct Vector3 : public MallocOperation
    {
        typedef typename std::conditional<std::is_floating_point<T>::value, T, float>::type PrecisionType;

        union
        {
            T data[3];
            struct { T x, y, z; };
            struct { T r, g, b; };
        };

        Vector3<T>() : x(0), y(0), z(0) {};
        Vector3<T>(const Vector3<T>& v) = default;
        explicit Vector3<T>(const T& v) : x(v), y(v), z(v) {};
        Vector3<T>(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {};

        T& operator[](int idx)
        {
            MIKASA_ASSERT(idx < 3);
            return data[idx];
        }

        inline bool operator==(const Vector3<T>& rhs) const noexcept
        {
            return comparison_traits<T>::equal(x, rhs.x)
                   && comparison_traits<T>::equal(y, rhs.y)
                   && comparison_traits<T>::equal(z, rhs.z);
        }

        inline bool operator!=(const Vector3<T>& rhs) const noexcept
        {
            return !comparison_traits<T>::equal(x, rhs.x)
                   || !comparison_traits<T>::equal(y, rhs.y)
                   || !comparison_traits<T>::equal(z, rhs.z);
        }

        inline Vector3<T> operator+(const Vector3<T>& rhs) const noexcept
        {
            return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        inline Vector3<T> operator-(const Vector3<T>& rhs) const noexcept
        {
            return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        inline Vector3<T> operator*(T scale)  const noexcept
        {
            return Vector3<T>(x * scale, y * scale, z * scale);
        }

        friend inline Vector3<T> operator*(T scale, const Vector3<T>& rhs) noexcept
        {
            return Vector3<T>(rhs.x * scale, rhs.y * scale, rhs.z * scale);
        }

        inline PrecisionType Dot(const Vector3<T>& rhs) const noexcept
        {
            PrecisionType result = 0;
            result += x * rhs.x;
            result += y * rhs.y;
            result += z * rhs.z;
            return result;
        }

        inline Vector3<T> Cross(const Vector3<T>& rhs) const noexcept
        {
            Vector3<T> result;
            result[0] = data[1] * rhs.data[2] - data[2] * rhs.data[1];
            result[1] = data[2] * rhs.data[0] - data[0] * rhs.data[2];
            result[2] = data[0] * rhs.data[1] - data[1] * rhs.data[0];
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

        inline Vector3<T> Normalized() const noexcept
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
        }
    };

    typedef Vector3<int> Vector3i;
    typedef Vector3<float> Vector3f;
    typedef Vector3<double> Vector3d;
}


