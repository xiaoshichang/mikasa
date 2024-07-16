#pragma once
#include "../RHIShaderResourceView.h"

namespace mikasa::Runtime::Core
{
    class RHIShaderResourceViewDX11 : public RHIShaderResourceView
    {
    public:
        RHIShaderResourceViewDX11();
        ~RHIShaderResourceViewDX11() override;
    };
}
