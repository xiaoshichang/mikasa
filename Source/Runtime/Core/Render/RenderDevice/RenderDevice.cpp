
#include "RenderDevice.h"
#include "Runtime/Foundation/Foundation.h"

#ifdef MIKASA_TARGET_PLATFORM_Window
#include "RHI/DX11/RHIDX11.h"
#endif

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

RHI* RenderDevice::RHI = nullptr;
RenderCommandQueue* RenderDevice::RenderCommandQueue_ = nullptr;

void RenderDevice::Init(const ApplicationInitParam& param, const WindowHandler& windowHandler)
{
    MIKASA_ASSERT(RHI == nullptr);
    RHI = new RHIDX11();
    RHI->InitRHI(param, windowHandler);

    RenderCommandQueue_ = new RenderCommandQueue();
}

void RenderDevice::UnInit()
{
    MIKASA_ASSERT(RenderCommandQueue_ != nullptr);
    delete RenderCommandQueue_;
    RenderCommandQueue_ = nullptr;


    MIKASA_ASSERT(RHI != nullptr);
    RHI->UnInitRHI();
    delete RHI;
    RHI = nullptr;
}

bool RenderDevice::ProcessOneRenderCommand()
{
    auto command = RenderCommandQueue_->Dequeue();
    if (command == nullptr)
    {
        return false;
    }

    command->Execute(RHI);
    // after render command executed, destroy it.
    delete command;
    return true;
}

void RenderDevice::FlushAllRenderCommand()
{
    while (ProcessOneRenderCommand())
    {
    }
}
