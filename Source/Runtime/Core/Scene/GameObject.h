#pragma once
#include "Runtime/Foundation/Foundation.h"
#include <string>
#include <vector>

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class GameObject
    {
    private:
        explicit GameObject(std::string name);
        ~GameObject();

    public:
        friend class Scene;

    private:
        std::string Name_;

    ///////////////////////////// transform //////////////////////////////////
    public:
        Vector3f GetPosition();
        void SetPosition(Vector3f position);
        Vector3f GetScale();
        void SetScale(Vector3f scale);
        Quaternion GetRotation();
        void SetRotation(Quaternion quaternion);
        Matrix4x4f GetWorldMatrix();

    private:
        Vector3f Position_ = Vector3f (0, 0, 0);
        Vector3f Scale_ = Vector3f (1, 1, 1);
        Quaternion Rotation_ = Quaternion::Identity();
        bool RTSDirty_ = true;
        Matrix4x4f RTS_ = Matrix4x4f::Identity();
    };
}


