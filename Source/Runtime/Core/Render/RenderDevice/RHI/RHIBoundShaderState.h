#pragma once

#include "RHIResource.h"

namespace mikasa::Runtime::Core
{
    class RHIBoundShaderState : public RHIResource
    {
    public:
        ~RHIBoundShaderState() override = default;
    };
}
