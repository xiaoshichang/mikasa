
#include "RHIVertexDeclaration.h"

using namespace mikasa::Runtime::Core;

uint32 VertexDeclarationElement::VertexElementTypeToStrike(VertexElementType type)
{
    switch (type)
    {
        case VertexElementType::VET_Float1:
            return sizeof(float);
        case VertexElementType::VET_Float2:
            return sizeof(float) * 2;
        case VertexElementType::VET_Float3:
            return sizeof(float) * 3;
        case VertexElementType::VET_Float4:
            return sizeof(float) * 4;
        case VertexElementType::VET_UByte4N:
        case VertexElementType::VET_Color:
            return 4;
        default:
            throw;
    }
}
