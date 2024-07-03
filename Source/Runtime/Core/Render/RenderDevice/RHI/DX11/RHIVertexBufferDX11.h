#ifdef MIKASA_TARGET_PLATFORM_Window
#pragma once
#include "../RHICommon.h"
#include "../RHIVertexBuffer.h"
#include <d3d11.h>

namespace mikasa::Runtime::Core
{
    class RHIVertexBufferDX11 : public RHIVertexBuffer
    {
    public:
        RHIVertexBufferDX11(ID3D11Device* device, RHIVertexBufferCreateInfo& createInfo);
        ~RHIVertexBufferDX11() override;
        ID3D11Buffer* GetInternal() const;

    private:
        ID3D11Buffer* Buffer_ = nullptr;

    };
}

#endif

