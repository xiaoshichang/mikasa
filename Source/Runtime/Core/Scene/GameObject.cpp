
#include "GameObject.h"

#include <utility>
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

GameObject::GameObject(Scene* scene, std::string name)
    : Scene_(scene)
    , Name_(std::move(name))
{
}

GameObject::~GameObject()
{
    if (StaticMeshRenderCmpt_ != nullptr)
    {
        UnInitStaticMeshRenderCmpt();
    }
    if (CameraCmpt_ != nullptr)
    {
        UnInitCameraCmpt();
    }
}

Scene *GameObject::GetScene() const
{
    return Scene_;
}

const std::string &GameObject::GetName() const
{
    return Name_;
}

Vector3f GameObject::GetPosition() const
{
    return Position_;
}

void GameObject::SetPosition(Vector3f position)
{
    Position_ = position;
    WorldMatrixDirty_ = true;
}

Vector3f GameObject::GetScale() const
{
    return Scale_;
}

void GameObject::SetScale(Vector3f scale)
{
    Scale_ = scale;
    WorldMatrixDirty_ = true;
}

Quaternion GameObject::GetRotation() const
{
    return Rotation_;
}

void GameObject::SetRotation(Quaternion rotation)
{
    Rotation_ = rotation;
    WorldMatrixDirty_ = true;
}

Matrix4x4f GameObject::GetWorldMatrix()
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

void GameObject::InitStaticMeshRenderCmpt()
{
    MIKASA_ASSERT(StaticMeshRenderCmpt_ == nullptr);
    StaticMeshRenderCmpt_ = new StaticMeshRenderCmpt(this);
}

void GameObject::UnInitStaticMeshRenderCmpt()
{
    MIKASA_ASSERT(StaticMeshRenderCmpt_ != nullptr);
    delete StaticMeshRenderCmpt_;
    StaticMeshRenderCmpt_ = nullptr;
}

StaticMeshRenderCmpt *GameObject::GetStaticMeshRenderCmpt()
{
    return StaticMeshRenderCmpt_;
}

void GameObject::InitCameraCmpt()
{
    MIKASA_ASSERT(CameraCmpt_ == nullptr);
    CameraCmpt_ = new CameraCmpt(this);
}

void GameObject::UnInitCameraCmpt()
{
    MIKASA_ASSERT(CameraCmpt_ != nullptr);
    delete CameraCmpt_;
    CameraCmpt_ = nullptr;
}

CameraCmpt *GameObject::GetCameraCmpt()
{
    return CameraCmpt_;
}

void GameObject::InitLightCmpt()
{
    MIKASA_ASSERT(LightCmpt_ == nullptr);
    LightCmpt_ = new LightCmpt(this);
}

void GameObject::UnInitLightCmpt()
{
    MIKASA_ASSERT(LightCmpt_ != nullptr);
    delete LightCmpt_;
    LightCmpt_ = nullptr;
}

LightCmpt *GameObject::GetLightCmpt()
{
    return LightCmpt_;
}




