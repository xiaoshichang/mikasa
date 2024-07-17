#pragma once

#include "../RHIShaderResourceView.h"
#include <d3d11.h>

namespace mikasa::Runtime::Core
{
    class RHIShaderResourceViewDX11 : public RHIShaderResourceView
    {
    public:
        explicit RHIShaderResourceViewDX11(ID3D11Device* device, ID3D11Resource* resource);
        ~RHIShaderResourceViewDX11() override;
        ID3D11ShaderResourceView* GetInternal();

    private:
        ID3D11ShaderResourceView* Internal_ = nullptr;
    };
}
