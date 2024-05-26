#pragma once

#include <string>
#include "Commom.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Runtime/Foundation/HAL/Memory/MAllocBase.h"

namespace mikasa::Runtime::Foundation
{
    template <typename T>
    struct Matrix4x4 : public MallocOperation
    {
        typedef typename std::conditional<std::is_floating_point<T>::value, T, float>::type PrecisionType;

        union
        {
            T data[4][4];
            Vector4<T> rows[4];
        };

        Matrix4x4()
        {
            memset(rows, 0, sizeof(Matrix4x4<T>));
        };

        Matrix4x4(T _00, T _01, T _02, T _03, T _10, T _11, T _12, T _13, T _20, T _21, T _22, T _23, T _30, T _31, T _32, T _33)
        {
            rows[0] = { _00 , _01, _02, _03 };
            rows[1] = { _10 , _11, _12, _13 };
            rows[2] = { _20 , _21, _22, _23 };
            rows[3] = { _30 , _31, _32, _33 };
        };

        Vector4<T>& operator[](int row)
        {
            return rows[row];
        }

        inline Matrix4x4<T>& operator=(const T* addr)
        {
            memcpy(data, addr,  sizeof(Matrix4x4<T>));
            return *this;
        }

        inline Matrix4x4<T>& operator=(const Matrix4x4<T>& rhs)
        {
            memcpy(data, rhs.data, sizeof(Matrix4x4<T>));
            return *this;
        }

        inline bool operator==(const Matrix4x4<T>& rhs) const noexcept
        {
            return rows[0] == rhs.rows[0]
                   && rows[1] == rhs.rows[1]
                   && rows[2] == rhs.rows[2]
                   && rows[3] == rhs.rows[3];
        }

        inline bool operator!=(const Matrix4x4<T>& rhs) const noexcept
        {
            return rows[0] != rhs.rows[0]
                   || rows[1] != rhs.rows[1]
                   || rows[2] != rhs.rows[2]
                   || rows[3] != rhs.rows[3];
        }

        inline Matrix4x4<T> operator+(const Matrix4x4<T>& rhs) const noexcept
        {
            Matrix4x4<T> r;
            r.rows[0] = rows[0] + rhs.rows[0];
            r.rows[1] = rows[1] + rhs.rows[1];
            r.rows[2] = rows[2] + rhs.rows[2];
            r.rows[3] = rows[3] + rhs.rows[3];
            return r;
        }

        inline Matrix4x4<T> operator-(const Matrix4x4<T>& rhs) const noexcept
        {
            Matrix4x4<T> r;
            r.rows[0] = rows[0] - rhs.rows[0];
            r.rows[1] = rows[1] - rhs.rows[1];
            r.rows[2] = rows[2] - rhs.rows[2];
            r.rows[3] = rows[3] - rhs.rows[3];
            return r;
        }

        inline Matrix4x4<T> operator*(const Matrix4x4<T>& rhs) const noexcept
        {
            Matrix4x4<T> r;
            float x = data[0][0];
            float y = data[0][1];
            float z = data[0][2];
            float w = data[0][3];
            // Perform the operation on the first row
            r.data[0][0] = (rhs.data[0][0] * x) + (rhs.data[1][0] * y) + (rhs.data[2][0] * z) + (rhs.data[3][0] * w);
            r.data[0][1] = (rhs.data[0][1] * x) + (rhs.data[1][1] * y) + (rhs.data[2][1] * z) + (rhs.data[3][1] * w);
            r.data[0][2] = (rhs.data[0][2] * x) + (rhs.data[1][2] * y) + (rhs.data[2][2] * z) + (rhs.data[3][2] * w);
            r.data[0][3] = (rhs.data[0][3] * x) + (rhs.data[1][3] * y) + (rhs.data[2][3] * z) + (rhs.data[3][3] * w);
            // Repeat for all the other rows
            x = data[1][0];
            y = data[1][1];
            z = data[1][2];
            w = data[1][3];
            r.data[1][0] = (rhs.data[0][0] * x) + (rhs.data[1][0] * y) + (rhs.data[2][0] * z) + (rhs.data[3][0] * w);
            r.data[1][1] = (rhs.data[0][1] * x) + (rhs.data[1][1] * y) + (rhs.data[2][1] * z) + (rhs.data[3][1] * w);
            r.data[1][2] = (rhs.data[0][2] * x) + (rhs.data[1][2] * y) + (rhs.data[2][2] * z) + (rhs.data[3][2] * w);
            r.data[1][3] = (rhs.data[0][3] * x) + (rhs.data[1][3] * y) + (rhs.data[2][3] * z) + (rhs.data[3][3] * w);
            x = data[2][0];
            y = data[2][1];
            z = data[2][2];
            w = data[2][3];
            r.data[2][0] = (rhs.data[0][0] * x) + (rhs.data[1][0] * y) + (rhs.data[2][0] * z) + (rhs.data[3][0] * w);
            r.data[2][1] = (rhs.data[0][1] * x) + (rhs.data[1][1] * y) + (rhs.data[2][1] * z) + (rhs.data[3][1] * w);
            r.data[2][2] = (rhs.data[0][2] * x) + (rhs.data[1][2] * y) + (rhs.data[2][2] * z) + (rhs.data[3][2] * w);
            r.data[2][3] = (rhs.data[0][3] * x) + (rhs.data[1][3] * y) + (rhs.data[2][3] * z) + (rhs.data[3][3] * w);
            x = data[3][0];
            y = data[3][1];
            z = data[3][2];
            w = data[3][3];
            r.data[3][0] = (rhs.data[0][0] * x) + (rhs.data[1][0] * y) + (rhs.data[2][0] * z) + (rhs.data[3][0] * w);
            r.data[3][1] = (rhs.data[0][1] * x) + (rhs.data[1][1] * y) + (rhs.data[2][1] * z) + (rhs.data[3][1] * w);
            r.data[3][2] = (rhs.data[0][2] * x) + (rhs.data[1][2] * y) + (rhs.data[2][2] * z) + (rhs.data[3][2] * w);
            r.data[3][3] = (rhs.data[0][3] * x) + (rhs.data[1][3] * y) + (rhs.data[2][3] * z) + (rhs.data[3][3] * w);
            return r;
        }


        inline Matrix4x4<PrecisionType> Inverse(PrecisionType* pDeterminant)
        {
            Matrix4x4<T> transposed = Transpose();
            Vector4<T> temp0[4], temp1[4];

            temp0[0] = { transposed.rows[2].x, transposed.rows[2].x , transposed.rows[2].y, transposed.rows[2].y };
            temp1[0] = { transposed.rows[3].z, transposed.rows[3].w , transposed.rows[3].z, transposed.rows[3].w };
            temp0[1] = { transposed.rows[0].x, transposed.rows[0].x , transposed.rows[0].y, transposed.rows[0].y };
            temp1[1] = { transposed.rows[1].z, transposed.rows[1].w , transposed.rows[1].z, transposed.rows[1].w };
            temp0[2] = { transposed.rows[2].x, transposed.rows[2].z , transposed.rows[0].x, transposed.rows[0].z };
            temp1[2] = { transposed.rows[3].y, transposed.rows[3].w , transposed.rows[1].y, transposed.rows[1].w };

            Vector4<T> D0 = temp0[0] * temp1[0];
            Vector4<T> D1 = temp0[1] * temp1[1];
            Vector4<T> D2 = temp0[2] * temp1[2];

            temp0[0] = { transposed.rows[2].z, transposed.rows[2].w , transposed.rows[2].z, transposed.rows[2].w };
            temp1[0] = { transposed.rows[3].x, transposed.rows[3].x , transposed.rows[3].y, transposed.rows[3].y };
            temp0[1] = { transposed.rows[0].z, transposed.rows[0].w , transposed.rows[0].z, transposed.rows[0].w };
            temp1[1] = { transposed.rows[1].x, transposed.rows[1].x , transposed.rows[1].y, transposed.rows[1].y };
            temp0[2] = { transposed.rows[2].y, transposed.rows[2].w , transposed.rows[0].y, transposed.rows[0].w };
            temp1[2] = { transposed.rows[3].x, transposed.rows[3].z , transposed.rows[1].x, transposed.rows[1].z };

            D0 = D0 - (temp0[0] * temp1[0]);
            D1 = D1 - (temp0[1] * temp1[1]);
            D2 = D2 - (temp0[2] * temp1[2]);

            temp0[0] = { transposed.rows[1].y, transposed.rows[1].z, transposed.rows[1].x, transposed.rows[1].y };
            temp1[0] = { D2.y, D0.y, D0.w, D0.x };
            temp0[1] = { transposed.rows[0].z, transposed.rows[0].x, transposed.rows[0].y, transposed.rows[0].x };
            temp1[1] = { D0.w, D2.y, D0.y, D0.z };
            temp0[2] = { transposed.rows[3].y, transposed.rows[3].z, transposed.rows[3].x, transposed.rows[3].y };
            temp1[2] = { D2.w, D1.y, D1.w, D1.x };
            temp0[3] = { transposed.rows[2].z, transposed.rows[2].x, transposed.rows[2].y, transposed.rows[2].x };
            temp1[3] = { D1.w, D2.w, D1.y, D1.z };

            Vector4<T> C0 = temp0[0] * temp1[0];
            Vector4<T> C2 = temp0[1] * temp1[1];
            Vector4<T> C4 = temp0[2] * temp1[2];
            Vector4<T> C6 = temp0[3] * temp1[3];

            temp0[0] = { transposed.rows[1].z, transposed.rows[1].w, transposed.rows[1].y, transposed.rows[1].z };
            temp1[0] = { D0.w, D0.x, D0.y, D2.x };
            temp0[1] = { transposed.rows[0].w, transposed.rows[0].z, transposed.rows[0].w, transposed.rows[0].y };
            temp1[1] = { D0.z, D0.y, D2.x, D0.x };
            temp0[2] = { transposed.rows[3].z, transposed.rows[3].w, transposed.rows[3].y, transposed.rows[3].z };
            temp1[2] = { D1.w, D1.x, D1.y, D2.z };
            temp0[3] = { transposed.rows[2].w, transposed.rows[2].z, transposed.rows[2].w, transposed.rows[2].y };
            temp1[3] = { D1.z, D1.y, D2.z, D1.x };

            C0 = C0 - (temp0[0] * temp1[0]);
            C2 = C2 - (temp0[1] * temp1[1]);
            C4 = C4 - (temp0[2] * temp1[2]);
            C6 = C6 - (temp0[3] * temp1[3]);

            temp0[0] = { transposed.rows[1].w, transposed.rows[1].x, transposed.rows[1].w, transposed.rows[1].x };
            temp1[0] = { D0.z, D2.y, D2.x, D0.z };
            temp0[1] = { transposed.rows[0].y, transposed.rows[0].w, transposed.rows[0].x, transposed.rows[0].z };
            temp1[1] = { D2.y, D0.x, D0.w, D2.x };
            temp0[2] = { transposed.rows[3].w, transposed.rows[3].x, transposed.rows[3].w, transposed.rows[3].x };
            temp1[2] = { D1.z, D2.w, D2.z, D1.z };
            temp0[3] = { transposed.rows[2].y, transposed.rows[2].w, transposed.rows[2].x, transposed.rows[2].z };
            temp1[3] = { D2.w, D1.x, D1.w, D2.z };

            Vector4<T> C1 = C0 - (temp0[0] * temp1[0]);
            C0 = (temp0[0] * temp1[0]) + C0;
            Vector4<T> C3 = C2 + (temp0[1] * temp1[1]);
            C2 = C2 - (temp0[1] * temp1[1]);
            Vector4<T> C5 = C4 - (temp0[2] * temp1[2]);
            C4 = (temp0[2] * temp1[2]) + C4;
            Vector4<T> C7 = C6 + (temp0[3] * temp1[3]);
            C6 = C6 - (temp0[3] * temp1[3]);

            Matrix4x4<PrecisionType> adj = {};
            adj.rows[0] = { C0.x, C1.y, C0.z, C1.w };
            adj.rows[1] = { C2.x, C3.y, C2.z, C3.w };
            adj.rows[2] = { C4.x, C5.y, C4.z, C5.w };
            adj.rows[3] = { C6.x, C7.y, C6.z, C7.w };

            PrecisionType determinant = adj.rows[0].Dot(transposed.rows[0]);
            if (pDeterminant != nullptr)
            {
                *pDeterminant = determinant;
            }

            PrecisionType reciprocal = 1 / determinant;
            Matrix4x4<PrecisionType> result = {};
            result.rows[0] = adj.rows[0] * reciprocal;
            result.rows[1] = adj.rows[1] * reciprocal;
            result.rows[2] = adj.rows[2] * reciprocal;
            result.rows[3] = adj.rows[3] * reciprocal;
            return result;
        }

        inline Matrix4x4<T> operator*(const T& scale) const noexcept
        {
            Matrix4x4<T> r = {};
            r.rows[0] = rows[0] * scale;
            r.rows[1] = rows[1] * scale;
            r.rows[2] = rows[2] * scale;
            r.rows[3] = rows[3] * scale;
            return r;
        }

        inline Vector3f TransformPoint(const Vector3f& point) const noexcept
        {
            Vector4f hSpace = Vector4f(point.x, point.y, point.z, 1);
            Vector3f r = Vector3f(0, 0, 0);
            r[0] = hSpace.Dot(rows[0]);
            r[1] = hSpace.Dot(rows[1]);
            r[2] = hSpace.Dot(rows[2]);
            return r;
        }

        inline Vector3f TransformVector(const Vector3f& vector) const noexcept
        {
            Vector4f hSpace = Vector4f(vector.x, vector.y, vector.z, 0);
            Vector3f r = Vector3f(0, 0, 0);
            r[0] = hSpace.Dot(rows[0]);
            r[1] = hSpace.Dot(rows[1]);
            r[2] = hSpace.Dot(rows[2]);
            return r;
        }

        Matrix4x4<T> Transpose() const noexcept
        {
            Matrix4x4<T> r = {};
            r.data[0][0] = data[0][0];
            r.data[0][1] = data[1][0];
            r.data[0][2] = data[2][0];
            r.data[0][3] = data[3][0];

            r.data[1][0] = data[0][1];
            r.data[1][1] = data[1][1];
            r.data[1][2] = data[2][1];
            r.data[1][3] = data[3][1];

            r.data[2][0] = data[0][2];
            r.data[2][1] = data[1][2];
            r.data[2][2] = data[2][2];
            r.data[2][3] = data[3][2];

            r.data[3][0] = data[0][3];
            r.data[3][1] = data[1][3];
            r.data[3][2] = data[2][3];
            r.data[3][3] = data[3][3];
            return r;
        }

        inline void TransposeInPlace() noexcept
        {
            Matrix4x4<T> temp = Transpose();
            *this = temp;
        }

        inline static Matrix4x4<T> Identity() noexcept
        {
            Matrix4x4<T> r;
            r.data[0][0] = 1;
            r.data[1][1] = 1;
            r.data[2][2] = 1;
            r.data[3][3] = 1;
            return r;
        }

    };

    typedef Matrix4x4<int> Matrix4x4i;
    typedef Matrix4x4<float> Matrix4x4f;
    typedef Matrix4x4<double> Matrix4x4d;
}



