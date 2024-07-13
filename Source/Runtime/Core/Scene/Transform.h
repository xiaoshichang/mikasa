#pragma once
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class Transform
    {
    public:
        Vector3f GetPosition() const;
        void SetPosition(Vector3f position);
        Vector3f GetScale() const;
        void SetScale(Vector3f scale);
        Quaternion GetRotation() const;
        void SetRotation(Quaternion quaternion);
        void SetRotation(float x, float y, float z);
        void LookAt(Vector3f target, Vector3f up);
        Matrix4x4f GetWorldMatrix();

        Vector3f Forward();
        Vector3f Up();

    private:
        Vector3f Position_ = Vector3f (0, 0, 0);
        Vector3f Scale_ = Vector3f (1, 1, 1);
        Quaternion Rotation_ = Quaternion::Identity();
        bool WorldMatrixDirty_ = true;
        Matrix4x4f WorldMatrix_ = Matrix4x4f::Identity();
    };

}
