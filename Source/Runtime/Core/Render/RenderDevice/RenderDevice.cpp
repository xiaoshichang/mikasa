
#include "RenderDevice.h"
#include "../RHI/RHI.h"
#include "Runtime/Foundation/Foundation.h"

#ifdef MIKASA_TARGET_PLATFORM_Window
#include "../RHI/DX12/RHIDX12.h"
#include "../RHI/DX11/RHIDX11.h"
#endif

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

RHI* RenderDevice::RHI_ = nullptr;

void RenderDevice::Init(const ApplicationInitParam& param, const WindowHandler& windowHandler)
{
    MIKASA_ASSERT(RHI_ == nullptr);
    RHI_ = new RHIDX11();
    RHI_->InitRHI(param, windowHandler);
}

void RenderDevice::UnInit()
{
    MIKASA_ASSERT(RHI_ != nullptr);
    RHI_->UnInitRHI();
    delete RHI_;
    RHI_ = nullptr;
}

void RenderDevice::ProcessRenderCommand(RenderCommandBase *command)
{
    command->Execute(RHI_);

    // after render command executed, destroy it.
    delete command;
}
