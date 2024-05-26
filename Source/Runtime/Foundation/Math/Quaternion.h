#pragma once

#include <algorithm>    // std::clamp

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"



namespace mikasa::Runtime::Foundation
{
    inline void ThreeAxisRot(float r11, float r12, float r21, float r31, float r32, float res[])
    {
        res[0] = atan2(r31, r32);
        r21 = std::clamp(r21, -1.0f, 1.0f);
        res[1] = asin(r21);
        res[2] = atan2(r11, r12);
    }

    struct Quaternion : public MallocOperation
    {
        float x, y, z, w;

        Quaternion():x(0),y(0),z(0),w(1){}
        Quaternion(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {}

        inline bool operator==(const Quaternion& rhs) const
        {
            return comparison_traits<float>::equal(x, rhs.x)
                   && comparison_traits<float>::equal(y, rhs.y)
                   && comparison_traits<float>::equal(z, rhs.z)
                   && comparison_traits<float>::equal(w, rhs.w);
        }

        inline bool operator!=(const Quaternion& rhs) const
        {
            return !comparison_traits<float>::equal(x, rhs.x)
                   || !comparison_traits<float>::equal(y, rhs.y)
                   || !comparison_traits<float>::equal(z, rhs.z)
                   || !comparison_traits<float>::equal(w, rhs.w);
        }

        inline float operator+(const Quaternion& rhs) const
        {
            Vector3f v1(x, y, z);
            Vector3f v2(rhs.x, rhs.y, rhs.z);
            return w * rhs.w + v1.Dot(v2);
        }

        inline Quaternion operator*(const Quaternion& rhs) const
        {
            Vector3f v1(x, y, z);
            Vector3f v2(rhs.x, rhs.y, rhs.z);
            Vector3f xyz = v1.Cross(v2) + v1 * rhs.w + v2 * w;
            float real = w * rhs.w - v1.Dot(v2);
            return { real, xyz.x, xyz.y, xyz.z };
        }

        inline static Quaternion Identity()
        {
            return { 0, 0, 0, 1 };
        }

        inline Quaternion Normalized()
        {
            auto temp = *this;
            temp.NormalizedInPlace();
            return temp;
        }

        inline void NormalizedInPlace()
        {
            Vector4f v(x, y, z, w);
            v.NormalizedInPlace();
            x = v.x;
            y = v.y;
            z = v.z;
            w = v.w;
        }

        inline Quaternion Inverse() const
        {
            Quaternion Result;
            float LengthSq = x * x + y * y + z * z + w * w;
            Result.x = -x / LengthSq;
            Result.y = -y / LengthSq;
            Result.z = -z / LengthSq;
            Result.w = w / LengthSq;
            return Result;
        }

        // rotations are performed around the Z axis, the X axis, and the Y axis, in that order.
        // http://www.andre-gaschler.com/rotationconverter/
        // https://www.cnblogs.com/21207-ihome/p/6894128.html
        // enum RotSeq{zyx, zyz, zxy, zxz, yxz, yxy, yzx, yzy, xyz, xyx, xzy,xzx};
        // using yxz, result is ZXY, so return res[1], res[2], res[0]
        Vector3f ToEuler()
        {
            Quaternion q = *this;
            float res[3];
            ThreeAxisRot(2 * (q.x * q.z + q.w * q.y),
                         q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z,
                         -2 * (q.y * q.z - q.w * q.x),
                         2 * (q.x * q.y + q.w * q.z),
                         q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z,
                         res);
            return { res[1], res[2], res[0] };
        }


        // https://docs.microsoft.com/en-us/windows/win32/api/directxmath/nf-directxmath-xmquaternionrotationrollpitchyaw
        // The order of transformations is roll(z) first, then pitch(x), then yaw(y).
        inline static Quaternion FromRollPitchYawLH(float pitch, float yaw, float roll)
        {
            const float halfpitch = pitch * 0.5f;
            float cp = cosf(halfpitch);
            float sp = sinf(halfpitch);

            const float halfyaw = yaw * 0.5f;
            float cy = cosf(halfyaw);
            float sy = sinf(halfyaw);

            const float halfroll = roll * 0.5f;
            float cr = cosf(halfroll);
            float sr = sinf(halfroll);

            float x = cr * sp * cy + sr * cp * sy;
            float y = cr * cp * sy - sr * sp * cy;
            float z = sr * cp * cy - cr * sp * sy;
            float w = cr * cp * cy + sr * sp * sy;
            return Quaternion(x, y, z, w);
        }

        // https://docs.microsoft.com/en-us/windows/win32/api/directxmath/nf-directxmath-xmquaternionrotationrollpitchyaw
        // To use right-handed coordinates, negate all three angles.
        inline static Quaternion FromRollPitchYawRH(float pitch, float yaw, float roll)
        {
            return FromRollPitchYawLH(-pitch, -yaw, -roll);
        }

    };
}

