
#include "Renderer.h"
#include "../RenderDevice/RenderDevice.h"

using namespace mikasa::Runtime::Core;

Renderer::Renderer(const std::shared_ptr<RenderScene>& scene,  const std::shared_ptr<RenderViewInfo>& vf)
    : RenderScene_(scene)
    , ViewInfo_(vf)
{
}

Renderer::~Renderer()
{
    RenderScene_.reset();
    ViewInfo_.reset();
}





