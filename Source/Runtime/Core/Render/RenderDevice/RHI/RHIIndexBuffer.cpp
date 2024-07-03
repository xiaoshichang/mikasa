
#include "RHIIndexBuffer.h"

using namespace mikasa::Runtime::Core;

RHIIndexBuffer::RHIIndexBuffer(IndexBufferElementType elementType)
    : ElementType_(elementType)
{

}

RHIIndexBuffer::~RHIIndexBuffer()
{

}

IndexBufferElementType RHIIndexBuffer::GetElementType() const
{
    return ElementType_;
}
