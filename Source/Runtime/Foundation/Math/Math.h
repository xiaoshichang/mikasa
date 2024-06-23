
#pragma once

#include "Commom.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

namespace mikasa::Runtime::Foundation
{
    template<typename T>
    static inline T Clamp(T minv, T maxv, T t)
    {
        if (t < minv)
        {
            return minv;
        }
        if (t > maxv)
        {
            return maxv;
        }
        return t;
    }

    static inline Matrix4x4f MatrixTranslation(float x, float y, float z) noexcept
    {
        Matrix4x4f translation =
                {
                        1.0f, 0.0f, 0.0f,    x ,
                        0.0f, 1.0f, 0.0f,    y ,
                        0.0f, 0.0f, 1.0f,    z ,
                        0.0f, 0.0f, 0.0f, 1.0f
                };
        return translation;
    }

    static inline Matrix4x4f BuildTranslationMatrix(const Vector3f& position) noexcept
    {
        Matrix4x4f translation =
                {
                        1.0f, 0.0f, 0.0f,    position.x ,
                        0.0f, 1.0f, 0.0f,    position.y ,
                        0.0f, 0.0f, 1.0f,    position.z ,
                        0.0f, 0.0f, 0.0f,			1.0f
                };
        return translation;
    }


    static inline Matrix4x4f MatrixScaling(float x, float y, float z) noexcept
    {
        Matrix4x4f scale =
                {
                        x, 0.0f, 0.0f, 0.0f ,
                        0.0f,    y, 0.0f, 0.0f ,
                        0.0f, 0.0f,    z, 0.0f ,
                        0.0f, 0.0f, 0.0f, 1.0f ,
                };
        return scale;
    }

    static inline Matrix4x4f BuildScalingMatrix(const Vector3f& s) noexcept
    {
        Matrix4x4f scale =
                {
                        s.x, 0.0f, 0.0f, 0.0f ,
                        0.0f,  s.y, 0.0f, 0.0f ,
                        0.0f, 0.0f,  s.z, 0.0f ,
                        0.0f, 0.0f, 0.0f, 1.0f ,
                };
        return scale;
    }

    static inline Matrix4x4f MatrixRotationX(const float radio) noexcept
    {
        float c = cosf(radio), s = sinf(radio);
        Matrix4x4f tmp =
                {
                        1.0f,	0.0f, 0.0f, 0.0f ,
                        0.0f,	   c,   -s, 0.0f ,
                        0.0f,     s,    c, 0.0f ,
                        0.0f,  0.0f, 0.0f, 1.0f
                };
        return tmp;
    }


    static inline Matrix4x4f MatrixRotationY(const float radio) noexcept
    {
        float c = cosf(radio), s = sinf(radio);
        Matrix4x4f tmp =
                {
                        c,	0.0f,    s, 0.0f ,
                        0.0f,	1.0f, 0.0f, 0.0f ,
                        -s, 0.0f,    c, 0.0f ,
                        0.0f, 0.0f, 0.0f, 1.0f
                };
        return tmp;
    }


    static inline Matrix4x4f MatrixRotationZ(const float radio) noexcept
    {
        float c = cosf(radio), s = sinf(radio);
        Matrix4x4f tmp = {
                c,	  -s, 0.0f, 0.0f ,
                s,	   c, 0.0f, 0.0f ,
                0.0f, 0.0f, 1.0f, 0.0f ,
                0.0f, 0.0f, 0.0f, 1.0f
        };
        return tmp;
    }

    static inline Matrix4x4f MatrixRotationYawPitchRollLH(const float pitch, const float yaw, const float roll) noexcept
    {
        float cp = cosf(pitch);
        float sp = sinf(pitch);
        float cy = cosf(yaw);
        float sy = sinf(yaw);
        float cr = cosf(roll);
        float sr = sinf(roll);
        Matrix4x4f M = {};
        M.data[0][0] = cr * cy + sr * sp * sy;
        M.data[0][1] = sr * cp;
        M.data[0][2] = sr * sp * cy - cr * sy;
        M.data[0][3] = 0.0f;

        M.data[1][0] = cr * sp * sy - sr * cy;
        M.data[1][1] = cr * cp;
        M.data[1][2] = sr * sy + cr * sp * cy;
        M.data[1][3] = 0.0f;

        M.data[2][0] = cp * sy;
        M.data[2][1] = -sp;
        M.data[2][2] = cp * cy;
        M.data[2][3] = 0.0f;

        M.data[3][0] = 0.0f;
        M.data[3][1] = 0.0f;
        M.data[3][2] = 0.0f;
        M.data[3][3] = 1.0f;
        M.TransposeInPlace();

        return M;
    }

    static inline Matrix4x4f MatrixRotationYawPitchRollRH(const float pitch, const float yaw, const float roll) noexcept
    {
        return MatrixRotationYawPitchRollLH(-pitch, -yaw, -roll);
    }

    static inline Matrix4x4f __MatrixLookAtLH(const Vector3f& EyePosition, const Vector3f& EyeDirection, const Vector3f& UpDirection) noexcept
    {
        auto R2 = EyeDirection.Normalized();
        auto R0 = UpDirection.Cross(R2);
        R0.NormalizedInPlace();
        auto R1 = R2.Cross(R0);
        auto NegEyePosition = EyePosition * -1;
        auto D0 = R0.Dot(NegEyePosition);
        auto D1 = R1.Dot(NegEyePosition);
        auto D2 = R2.Dot(NegEyePosition);

        Matrix4x4f M =
                {
                        R0.x,	R0.y, R0.z,   D0,
                        R1.x,	R1.y, R1.z,   D1,
                        R2.x,	R2.y, R2.z,   D2,
                        0,	   0,	 0,  1.0f
                };
        return M;
    }

    static inline Matrix4x4f MatrixLookAtRH(const Vector3f& EyePosition, const Vector3f& FocusPosition, const Vector3f& UpDirection) noexcept
    {
        auto NegEyeDirection = EyePosition - FocusPosition;
        return __MatrixLookAtLH(EyePosition, NegEyeDirection, UpDirection);
    }

    static inline Matrix4x4f MatrixLookAtLH(const Vector3f& EyePosition, const Vector3f& FocusPosition, const Vector3f& UpDirection) noexcept
    {
        auto EyeDirection = FocusPosition - EyePosition;
        return __MatrixLookAtLH(EyePosition, EyeDirection, UpDirection);
    }

    /// <summary>
    /// https://github.com/g-truc/glm/blob/b3f87720261d623986f164b2a7f6a0a938430271/glm/ext/matrix_clip_space.inl
    /// left hand eye space -> left hand clip space.
    /// z range map to [0, 1]
    /// </summary>
    static inline Matrix4x4f MatrixPerspectiveFovLH01(const float FovInRadian, const float AspectRatio, const float NearZ, const float FarZ) noexcept
    {
        float tanHalfFovY = tanf(FovInRadian / 2.0f);
        Matrix4x4f matrix;
        matrix[0][0] = 1.0f / (AspectRatio * tanHalfFovY);
        matrix[1][1] = 1.0f / tanHalfFovY;
        matrix[2][2] = FarZ / (FarZ - NearZ);
        matrix[3][2] = 1.0f;
        matrix[2][3] = -(FarZ * NearZ) / (FarZ - NearZ);
        return matrix;
    }

    /// <summary>
    /// left hand eye space -> left hand clip space
    /// z range map to [-1, 1]
    /// </summary>
    static inline Matrix4x4f MatrixPerspectiveFovLH11(const float FovAngleY, const float AspectRatio, const float NearZ, const float FarZ) noexcept
    {
        float tanHalfFovY = tanf(FovAngleY / 2.0f);
        Matrix4x4f matrix;
        matrix[0][0] = 1.0f / (AspectRatio * tanHalfFovY);
        matrix[1][1] = 1.0f / tanHalfFovY;
        matrix[2][2] = FarZ / (FarZ - NearZ);
        matrix[3][2] = 1.0f;
        matrix[2][3] = -(2 * FarZ * NearZ) / (FarZ - NearZ);
        return matrix;
    }

    /// <summary>
    /// left hand eye space -> left hand clip space.
    /// z range map to [0, 1]
    /// </summary>
    static inline Matrix4x4f MatrixOrthographicLH01(const float ViewWidth, const float ViewHeight, const float NearZ, const float FarZ) noexcept
    {
        float fRange = 1.0f / (FarZ - NearZ);
        Matrix4x4f matrix = {
                2.0f / ViewWidth,					 0.0f,				  0.0f,					  0.0f ,
                0.0f,					2.0f / ViewHeight,				  0.0f,					  0.0f ,
                0.0f,								 0.0f,				fRange,			-NearZ * fRange,
                0.0f,								 0.0f,				  0.0f,				      1.0f
        };
        return matrix;
    }

    /// <summary>
    /// left hand eye space -> left hand clip space.
    /// z range map to [-1, 1]
    /// </summary>
    static inline Matrix4x4f MatrixOrthographicLH11(const float ViewWidth, const float ViewHeight, const float NearZ, const float FarZ) noexcept
    {
        float fRange = 1.0f / (FarZ - NearZ);
        Matrix4x4f matrix = {
                2.0f / ViewWidth,					0.0f,				0.0f,						   0.0f ,
                0.0f,				   2.0f / ViewHeight,				0.0f,						   0.0f ,
                0.0f,								0.0f,			  fRange,		-(FarZ + NearZ) * fRange,
                0.0f,								0.0f,				0.0f,						   1.0f
        };
        return matrix;
    }


    /// Build rotation matrix from a quaternion
    /// note that transform from quaternion to rotation matrix does not involve handedness of any sort.
    /// see <<Derivation of Equations>> part of http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/
    /// P2 = q * P1 * q'
    /// P2 = [M] P1
    /// It is purely solve for the matrix M such that [M] P1 = q * P1 * q'
    /// https://stackoverflow.com/questions/1274936/flipping-a-quaternion-from-right-to-left-handed-coordinates
    static inline Matrix4x4f BuildRotationMatrixFromQuaternion(const Quaternion& q)
    {
        float qx = q.x;
        float qxx = qx * qx;
        float qy = q.y;
        float qyy = qy * qy;
        float qz = q.z;
        float qzz = qz * qz;
        float qw = q.w;
        Matrix4x4f m =
                {
                        1.f - 2.f * qyy - 2.f * qzz,       2.f * qx * qy - 2.f * qz * qw,      2.f * qx * qz + 2.f * qy * qw,      0.0f,
                        2.f * qx * qy + 2.f * qz * qw,     1.f - 2.f * qxx - 2.f * qzz,        2.f * qy * qz - 2.f * qx * qw,      0.0f,
                        2.f * qx * qz - 2.f * qy * qw,     2.f * qy * qz + 2.f * qx * qw,      1.f - 2.f * qxx - 2.f * qyy,        0.0f,
                        0.0f,                              0.0f,                               0.f,                                1.0f
                };
        return m;
    }

}