
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
}

StaticMeshRenderCmpt::~StaticMeshRenderCmpt()
{
    UnInitRenderThreadPart();
}

void StaticMeshRenderCmpt::InitRenderThreadPart()
{
    auto mesh = std::make_shared<StaticMesh>("");
    RenderProxy_ = std::make_shared<StaticMeshRenderProxy>(Owner_->GetTransform().GetWorldMatrix(), mesh);
    auto proxy = RenderProxy_;
    auto scene = Owner_->GetScene()->GetRenderScene();
    auto lambda = [=]()
    {
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
