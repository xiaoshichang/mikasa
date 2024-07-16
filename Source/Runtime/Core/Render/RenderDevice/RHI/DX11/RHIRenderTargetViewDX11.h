#ifdef MIKASA_TARGET_PLATFORM_Window

#pragma once
#include "Runtime/Core/Render/RenderDevice/RHI/RHIRenderTargetView.h"
#include <d3d11.h>

namespace mikasa::Runtime::Core
{
    class RHIRenderTargetViewDX11 : public RHIRenderTargetView
    {
    public:
        explicit RHIRenderTargetViewDX11(ID3D11Device* device, ID3D11Resource* resource);
        ~RHIRenderTargetViewDX11() override;

        ID3D11RenderTargetView* GetInternal() { return Internal_; }

    private:
        ID3D11RenderTargetView* Internal_ = nullptr;
    };
}

#endif


