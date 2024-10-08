
#include "SimpleForwardRenderer.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include "Runtime/Core/Render/RenderDevice/RenderResource/RenderTarget.h"
#include "Runtime/Framework/Application/Application.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Framework;

SimpleForwardRenderer::SimpleForwardRenderer(const std::shared_ptr<RenderScene>& scene, const std::shared_ptr<RenderViewFamily>& vf)
    : Renderer(scene, vf)
{
}

SimpleForwardRenderer::~SimpleForwardRenderer()
{
}

void SimpleForwardRenderer::RenderSingleView(const std::shared_ptr<RenderView> &view)
{
    auto viewWidth = view->Camera.GetViewWidthInPixel();
    auto viewHeight = view->Camera.GetViewHeightInPixel();
    RenderDevice::RHI->RSSetScissorRect(0, 0, (int)viewWidth, (int)viewHeight);
    RenderDevice::RHI->RSSetViewport(0, 0, viewWidth, viewHeight);
    RenderDevice::RHI->OMSetRenderTarget(ViewFamily_->RenderTarget->AsRenderTargetView());

    RenderSingleViewContext context;
    context.RenderView = view;

    for(auto& proxy : RenderScene_->GetAllStaticMeshRenderProxies())
    {
        proxy->Render(context);
    }
}
