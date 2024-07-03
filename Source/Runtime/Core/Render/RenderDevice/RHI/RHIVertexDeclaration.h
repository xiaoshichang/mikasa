#pragma once
#include "RHIResource.h"
#include "RHICommon.h"
#include "Runtime/Foundation/Foundation.h"

namespace mikasa::Runtime::Core
{


    /**
     * used to create RHIVertexDeclaration
     */
    struct VertexDeclarationElement
    {
        VertexDeclarationElement(VertexElementType type, uint8 slot, uint8 offset, uint8 attrIndex)
            : Type(type)
            , InputSlot(slot)
            , Offset(offset)
            , AttributeIndex(attrIndex)
        {
            Stride = VertexElementTypeToStrike(type);
        }

        VertexElementType Type;
        uint8 InputSlot;
        uint8 Offset;
        uint8 AttributeIndex;
        uint16 Stride;

        static uint32 VertexElementTypeToStrike(VertexElementType type);
    };


    /**
     * represents vertex input layout declaration without bounding to vertex shader
     */
    class RHIVertexDeclaration : public RHIResource
    {
    public:
        ~RHIVertexDeclaration() override = default;
    };
}

