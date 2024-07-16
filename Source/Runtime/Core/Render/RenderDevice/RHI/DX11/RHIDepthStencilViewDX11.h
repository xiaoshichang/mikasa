#pragma once
#include "../RHIDepthStencilView.h"

namespace mikasa::Runtime::Core
{
    class RHIDepthStencilViewDX11 : public RHIDepthStencilView
    {
    public:
        RHIDepthStencilViewDX11();
        ~RHIDepthStencilViewDX11() override;
    };

}