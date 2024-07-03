#pragma once

#include "Runtime/Foundation/Foundation.h"
#include "RHIResource.h"
#include "RHICommon.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class RHIIndexBuffer : public RHIResource
    {
    public:
        explicit RHIIndexBuffer(IndexBufferElementType elementType);
        ~RHIIndexBuffer() override;
        IndexBufferElementType GetElementType() const;

    protected:
        IndexBufferElementType ElementType_;

    };
}
