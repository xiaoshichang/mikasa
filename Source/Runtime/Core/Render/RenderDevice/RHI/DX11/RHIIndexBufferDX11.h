#ifdef MIKASA_TARGET_PLATFORM_Window
#pragma once

#include "../RHIIndexBuffer.h"
#include "../RHICommon.h"

#include <d3d11.h>

namespace mikasa::Runtime::Core
{
    class RHIIndexBufferDX11 : public RHIIndexBuffer
    {
    public:
        RHIIndexBufferDX11(ID3D11Device* device, RHIIndexBufferCreateInfo& createInfo);
        ~RHIIndexBufferDX11() override;
        ID3D11Buffer* GetInternal() const;
        DXGI_FORMAT GetFormat();

    private:
        ID3D11Buffer* Buffer_ = nullptr;
    };

}

#endif