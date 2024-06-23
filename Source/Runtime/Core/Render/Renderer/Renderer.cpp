
#include "Renderer.h"
#include "../RenderDevice/RenderDevice.h"

using namespace mikasa::Runtime::Core;

Renderer::Renderer(const std::shared_ptr<RenderViewInfo>& vf)
    : ViewInfo_(vf)
{

}

Renderer::~Renderer()
{
    ViewInfo_.reset();
}





