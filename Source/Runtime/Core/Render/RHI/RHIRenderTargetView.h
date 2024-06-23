#pragma once
#include "RHIResource.h"

namespace mikasa::Runtime::Core
{
    class RHIRenderTargetView : public RHIResource
    {
    public:
        RHIRenderTargetView() = default;
        ~RHIRenderTargetView() override = default;

    };
}

