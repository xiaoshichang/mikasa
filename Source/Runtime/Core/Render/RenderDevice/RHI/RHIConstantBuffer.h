#pragma once
#include "RHIResource.h"

namespace mikasa::Runtime::Core
{
    class RHIConstantBuffer : public RHIResource
    {
    public:
        RHIConstantBuffer();
        ~RHIConstantBuffer() override;
    };
}

