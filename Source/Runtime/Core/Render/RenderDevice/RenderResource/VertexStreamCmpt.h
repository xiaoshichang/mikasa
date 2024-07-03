#pragma once
#include "RenderResource.h"
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Core/Render/RenderDevice/RHI/RHIVertexBuffer.h"
#include "Runtime/Core/Render/RenderDevice/RHI/RHIVertexDeclaration.h"

namespace mikasa::Runtime::Core
{
    class VertexStreamCmpt : public RenderResource
    {
    public:
        VertexStreamCmpt(uint8* data, uint32 dataSize, VertexElementType elementType);
        ~VertexStreamCmpt() override;

        void InitRHIResource() override;
        const std::shared_ptr<RHIVertexBuffer>& GetVertexBuffer() const;
        uint32 GetVertexStrike() const;

    private:
        uint8* Data_;
        uint32 DataSize_;
        VertexElementType ElementType_;
        std::shared_ptr<RHIVertexBuffer> Buffer_;
    };
}
