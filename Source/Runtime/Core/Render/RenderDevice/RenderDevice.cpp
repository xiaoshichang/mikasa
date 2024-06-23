
#include "RenderDevice.h"
#include "Runtime/Foundation/Foundation.h"
#include "../RHI/RHI.h"
#include "../RenderCommand/RenderCommandQueue.h"

#ifdef MIKASA_TARGET_PLATFORM_Window
#include "../RHI/DX12/RHIDX12.h"
#include "../RHI/DX11/RHIDX11.h"
#endif

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

RHI* RenderDevice::RHI = nullptr;

void RenderDevice::Init(const ApplicationInitParam& param, const WindowHandler& windowHandler)
{
    MIKASA_ASSERT(RHI == nullptr);
    RHI = new RHIDX11();
    RHI->InitRHI(param, windowHandler);
}

void RenderDevice::UnInit()
{
    MIKASA_ASSERT(RHI != nullptr);
    RHI->UnInitRHI();
    delete RHI;
    RHI = nullptr;
}

bool RenderDevice::ProcessOneRenderCommand()
{
    auto command = RenderCommandQueue::Dequeue();
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
