
#include "GameObject.h"

#include <utility>
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

GameObject::GameObject(std::string name)
    : Name_(std::move(name))
{
}

GameObject::~GameObject()
{
}

Vector3f GameObject::GetPosition()
{
    return Position_;
}

void GameObject::SetPosition(Vector3f position)
{
    Position_ = position;
    RTSDirty_ = true;
}

Vector3f GameObject::GetScale()
{
    return Scale_;
}

void GameObject::SetScale(Vector3f scale)
{
    Scale_ = scale;
    RTSDirty_ = true;
}

Quaternion GameObject::GetRotation()
{
    return Rotation_;
}

void GameObject::SetRotation(Quaternion rotation)
{
    Rotation_ = rotation;
    RTSDirty_ = true;
}

Matrix4x4f GameObject::GetWorldMatrix()
{
    if (RTSDirty_)
    {
        auto r = BuildRotationMatrixFromQuaternion(Rotation_);
        auto t = BuildTranslationMatrix(Position_);
        auto s = BuildScalingMatrix(Scale_);
        RTS_ = t * s * r;
        RTSDirty_ = false;
    }
    return RTS_;
}


