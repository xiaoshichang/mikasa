#pragma once
#include "../RHIRenderTargetView.h"
#include <d3d11.h>

namespace mikasa::Runtime::Core
{
    class RHIRenderTargetViewDX11 : public RHIRenderTargetView
    {
    public:
        explicit RHIRenderTargetViewDX11(ID3D11Device* device, ID3D11Resource* resource);
        ~RHIRenderTargetViewDX11() override;

        ID3D11RenderTargetView* GetInternal() { return RTV_; }

    private:
        ID3D11RenderTargetView* RTV_ = nullptr;
    };
}


