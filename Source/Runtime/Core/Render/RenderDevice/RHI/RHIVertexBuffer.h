#pragma once

#include "Runtime/Foundation/Foundation.h"
#include "RHIResource.h"

using namespace mikasa::Runtime::Foundation;
namespace mikasa::Runtime::Core
{

    class RHIVertexBuffer : public RHIResource
    {
    public:
        RHIVertexBuffer();
        ~RHIVertexBuffer() override;

    };
}

