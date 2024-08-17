
#include "StaticMeshRenderCmpt.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include "Runtime/Core/Render/RenderDevice/RenderResource/StaticMesh.h"
#include "../GameObject.h"
#include "../Scene.h"

using namespace mikasa::Runtime::Core;

StaticMeshRenderCmpt::StaticMeshRenderCmpt(GameObject* owner)
    : Component(owner)
{
    InitRenderThreadPart();
    Owner_->GetTransform().OnTransformChange += OnTransformChangeDelegate::MemberFunctionDelegate(this, std::bind(&StaticMeshRenderCmpt::OnTransformChange, this));
}

StaticMeshRenderCmpt::~StaticMeshRenderCmpt()
{
    Owner_->GetTransform().OnTransformChange -= OnTransformChangeDelegate::MemberFunctionDelegate(this, std::bind(&StaticMeshRenderCmpt::OnTransformChange, this));
    UnInitRenderThreadPart();
}

void StaticMeshRenderCmpt::InitRenderThreadPart()
{
    auto mesh = std::make_shared<StaticMesh>("");
    auto transform = Owner_->GetTransform();

    RenderProxyTransform proxyTransform;
    proxyTransform.WorldPosition = transform.GetPosition();
    proxyTransform.WorldMatrix = transform.GetWorldMatrix();
    RenderProxy_ = std::make_shared<StaticMeshRenderProxy>(proxyTransform, mesh);

    auto proxy = RenderProxy_;
    auto scene = Owner_->GetScene()->GetRenderScene();
    auto lambda = [=]()
    {
        proxy->InitRHIResource();
        scene->AddStaticMeshRenderProxy(proxy);
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

void StaticMeshRenderCmpt::UnInitRenderThreadPart()
{
    auto proxy = RenderProxy_;
    auto scene = Owner_->GetScene()->GetRenderScene();
    auto lambda = [=]()
    {
        scene->RemoveStaticMeshRenderProxy(proxy);
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
    RenderProxy_.reset();
}

void StaticMeshRenderCmpt::OnTransformChange()
{
    auto scene = Owner_->GetScene()->GetRenderScene();
    auto& transform = Owner_->GetTransform();

    RenderProxyTransformUpdateInfo updateInfo;
    updateInfo.Proxy = RenderProxy_;
    updateInfo.Transform.WorldPosition = transform.GetPosition();
    updateInfo.Transform.WorldMatrix = transform.GetWorldMatrix();

    auto lambda = [=]()
    {
        scene->AddRenderProxyTransformUpdateInfo(updateInfo);
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}
