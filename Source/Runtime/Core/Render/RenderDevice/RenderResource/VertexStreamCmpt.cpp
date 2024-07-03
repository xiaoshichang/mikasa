
#include "VertexStreamCmpt.h"
#include "../RenderDevice.h"

using namespace mikasa::Runtime::Core;

VertexStreamCmpt::VertexStreamCmpt(uint8 *data, uint32 dataSize, VertexElementType elementType)
        :
        Data_(data),
        DataSize_(dataSize),
        ElementType_(elementType)
{
}

VertexStreamCmpt::~VertexStreamCmpt()
{
    Buffer_.reset();
}

void VertexStreamCmpt::InitRHIResource()
{
    RHIVertexBufferCreateInfo info(Data_, DataSize_);
    Data_ = nullptr;
    DataSize_ = 0;
    Buffer_ = RenderDevice::RHI->CreateVertexBuffer(info);
}

const std::shared_ptr<RHIVertexBuffer> &VertexStreamCmpt::GetVertexBuffer() const
{
    return Buffer_;
}

uint32 VertexStreamCmpt::GetVertexStrike() const
{
    return VertexDeclarationElement::VertexElementTypeToStrike(ElementType_);
}



