
#include "Renderer.h"
#include "../RenderDevice/RenderDevice.h"

using namespace mikasa::Runtime::Core;

Renderer::Renderer(const std::shared_ptr<RenderScene>& scene, const std::shared_ptr<RenderViewFamily>& vf)
    : RenderScene_(scene)
    , ViewFamily_(vf)
{
    MIKASA_ASSERT(scene != nullptr);
    MIKASA_ASSERT(vf != nullptr);
}

Renderer::~Renderer()
{
    RenderScene_.reset();
    ViewFamily_.reset();
}

void Renderer::Render()
{
    ViewFamily_->InitRHIResource();

    RenderDevice::RHI->ClearRenderTarget(ViewFamily_->RenderTarget, ViewFamily_->ClearColor);

    for(auto& view : ViewFamily_->Views)
    {
        RenderSingleView(view);
    }
}





