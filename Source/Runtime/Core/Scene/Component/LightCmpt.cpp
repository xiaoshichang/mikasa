
#include "LightCmpt.h"
#include "../Scene.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"

using namespace mikasa::Runtime::Core;

LightCmpt::LightCmpt(GameObject *owner) : Component(owner)
{
    InitRenderThreadPart();
}

LightCmpt::~LightCmpt()
{
    UnInitRenderThreadPart();
}

void LightCmpt::InitRenderThreadPart()
{
    RenderProxy_ = std::make_shared<LightRenderProxy>();
    auto proxy = RenderProxy_;
    auto scene = Owner_->GetScene()->GetRenderScene();
    auto lambda = [=]()
    {
        scene->AddLightRenderProxy(proxy);
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

void LightCmpt::UnInitRenderThreadPart()
{
    auto proxy = RenderProxy_;
    auto scene = Owner_->GetScene()->GetRenderScene();
    auto lambda = [=]()
    {
        scene->RemoveLightRenderProxy(proxy);
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
    RenderProxy_.reset();
}
