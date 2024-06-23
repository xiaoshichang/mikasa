
#include "RHIRenderTargetViewDX11.h"

using namespace mikasa::Runtime::Core;

RHIRenderTargetViewDX11::RHIRenderTargetViewDX11(ID3D11Device* device, ID3D11Resource* resource)
{
    if (device->CreateRenderTargetView(resource, nullptr, &RTV_) != S_OK)
    {
        throw;
    }
}

RHIRenderTargetViewDX11::~RHIRenderTargetViewDX11()
{
    RTV_->Release();
    RTV_ = nullptr;
}
