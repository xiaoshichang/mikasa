
#include "RenderViewFamily.h"
#include "RenderView.h"

using namespace mikasa::Runtime::Core;

RenderViewFamily::RenderViewFamily(const RenderViewFamilyInitializer& initializer)
    : Views(initializer.Views)
    , RenderTarget(initializer.RenderTarget)
    , ClearColor(initializer.ClearColor)
{
}

RenderViewFamily::~RenderViewFamily()
{
    Views.clear();
    RenderTarget = nullptr;
}

void RenderViewFamily::InitRHIResource()
{
    for (auto& view : Views)
    {
        view->InitRHIResource();
    }
}


