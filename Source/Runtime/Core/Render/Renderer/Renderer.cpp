
#include "Renderer.h"
#include "../RenderDevice/RenderDevice.h"

using namespace mikasa::Runtime::Core;

Renderer::Renderer(const std::shared_ptr<RenderScene>& scene,
                   const std::shared_ptr<RenderViewInfo>& vf,
                   RHIRenderTargetView* backBuffer)
    : RenderScene_(scene)
    , ViewInfo_(vf)
    , BackBuffer_(backBuffer)
{
    MIKASA_ASSERT(scene != nullptr);
    MIKASA_ASSERT(vf != nullptr);
    MIKASA_ASSERT(BackBuffer_ != nullptr);
}

Renderer::~Renderer()
{
    RenderScene_.reset();
    ViewInfo_.reset();
}





