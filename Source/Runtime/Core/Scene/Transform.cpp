
#include "Transform.h"

using namespace mikasa::Runtime::Core;

Vector3f Transform::GetPosition() const
{
    return Position_;
}

void Transform::SetPosition(Vector3f position)
{
    Position_ = position;
    WorldMatrixDirty_ = true;
}

Vector3f Transform::GetScale() const
{
    return Scale_;
}

void Transform::SetScale(Vector3f scale)
{
    Scale_ = scale;
    WorldMatrixDirty_ = true;
}

Quaternion Transform::GetRotation() const
{
    return Rotation_;
}

void Transform::SetRotation(Quaternion rotation)
{
    Rotation_ = rotation;
    WorldMatrixDirty_ = true;
}

void Transform::LookAt(Vector3f target, Vector3f up)
{
    auto rotation = MatrixLookAtLH(Position_, target, up);
    Rotation_ = Quaternion::FromRotationMatrix(rotation);
    WorldMatrixDirty_ = true;
}

Matrix4x4f Transform::GetWorldMatrix()
{
    if (WorldMatrixDirty_)
    {
        auto r = BuildRotationMatrixFromQuaternion(Rotation_);
        auto t = BuildTranslationMatrix(Position_);
        auto s = BuildScalingMatrix(Scale_);
        WorldMatrix_ = t * s * r;
        WorldMatrixDirty_ = false;
    }
    return WorldMatrix_;
}

Vector3f Transform::Forward()
{
    auto localForward = Vector3f (0, 0, 1);
    auto r = BuildRotationMatrixFromQuaternion(Rotation_);
    auto worldForward = r.TransformVector(localForward);
    return worldForward;
}

Vector3f Transform::Up()
{
    auto localForward = Vector3f (0, 1, 0);
    auto r = BuildRotationMatrixFromQuaternion(Rotation_);
    auto worldForward = r.TransformVector(localForward);
    return worldForward;
}


