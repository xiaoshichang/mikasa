#pragma once
#include "../RHIConstantBuffer.h"
#include "../RHICommon.h"
#include <d3d11.h>

namespace mikasa::Runtime::Core
{
    class RHIConstantBufferDX11 : public RHIConstantBuffer
    {
    public:
        explicit RHIConstantBufferDX11(ID3D11Device* device, RHIConstantBufferCreateInfo &createInfo);
        ~RHIConstantBufferDX11() override;
        ID3D11Buffer* GetInternal() const;

    private:
        ID3D11Buffer* Buffer_ = nullptr;
    };
}

