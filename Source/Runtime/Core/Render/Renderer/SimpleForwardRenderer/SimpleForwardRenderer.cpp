
#include "SimpleForwardRenderer.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"

using namespace mikasa::Runtime::Core;


SimpleForwardRenderer::SimpleForwardRenderer(const std::shared_ptr<RenderScene>& scene,  const std::shared_ptr<RenderViewInfo>& vf)
    : Renderer(scene, vf)
{
}

SimpleForwardRenderer::~SimpleForwardRenderer()
{
}

void SimpleForwardRenderer::Render()
{
    RenderDevice::RHI->RSSetScissorRect(0, 0, 1024, 768);
    RenderDevice::RHI->RSSetViewport(0, 0, 1024, 768);
    RenderDevice::RHI->ClearRenderTarget(ViewInfo_->Destination, ViewInfo_->ClearColor);
    RenderDevice::RHI->Present();
}




