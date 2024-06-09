
#include "RenderDevice.h"
#include "../RHI/RHI.h"
#include "Runtime/Foundation/Foundation.h"

#ifdef MIKASA_TARGET_PLATFORM_Window
#include "../RHI/DX12/RHIDX12.h"
#endif

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

RHI* RenderDevice::RHI_ = nullptr;

void RenderDevice::Init(const ApplicationInitParam& param, const WindowHandler& windowHandler)
{
    MIKASA_ASSERT(RHI_ == nullptr);
    RHI_ = new RHIDX12();
    RHI_->InitRHI(param, windowHandler);
}

void RenderDevice::UnInit()
{
    MIKASA_ASSERT(RHI_ != nullptr);
    // todo: wait last render frame finish before destroy rhi layer.
    RHI_->UnInitRHI();
    delete RHI_;
    RHI_ = nullptr;
}
