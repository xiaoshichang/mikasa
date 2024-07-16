#ifdef MIKASA_TARGET_PLATFORM_Window

#include "RHIRenderTargetViewDX11.h"

using namespace mikasa::Runtime::Core;

RHIRenderTargetViewDX11::RHIRenderTargetViewDX11(ID3D11Device* device, ID3D11Resource* resource)
{
    if (device->CreateRenderTargetView(resource, nullptr, &Internal_) != S_OK)
    {
        throw;
    }
}

RHIRenderTargetViewDX11::~RHIRenderTargetViewDX11()
{
    Internal_->Release();
    Internal_ = nullptr;
}

#endif