#pragma once
#include "RHIResource.h"

namespace mikasa::Runtime::Core
{
    class RHIDepthStencilView : public RHIResource
    {
    public:
        RHIDepthStencilView();
        ~RHIDepthStencilView() override;
    };

}
