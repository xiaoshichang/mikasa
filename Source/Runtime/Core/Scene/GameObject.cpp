
#include "GameObject.h"

#include <utility>
#include "Scene.h"
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
    if (LightCmpt_ != nullptr)
    {
        UnInitLightCmpt();
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
    Scene_->AddCameraToScene(CameraCmpt_);
}

void GameObject::UnInitCameraCmpt()
{
    MIKASA_ASSERT(CameraCmpt_ != nullptr);
    Scene_->RemoveCameraFromScene(CameraCmpt_);
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

Transform& GameObject::GetTransform()
{
    return Transform_;
}




