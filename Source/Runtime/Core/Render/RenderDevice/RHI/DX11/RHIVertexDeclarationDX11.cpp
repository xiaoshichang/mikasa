#include "RHIVertexDeclarationDX11.h"

using namespace mikasa::Runtime::Core;

RHIVertexDeclarationDX11::RHIVertexDeclarationDX11(const std::vector<VertexDeclarationElement> &elements)
{
    for (const auto& element : elements)
    {
        D3D11_INPUT_ELEMENT_DESC D3DElement = {nullptr};
        D3DElement.InputSlot = element.InputSlot;
        D3DElement.AlignedByteOffset = element.Offset;
        D3DElement.Format = ConvertFormat(element.Type);
        D3DElement.SemanticName = "ATTRIBUTE";
        D3DElement.SemanticIndex = element.AttributeIndex;
        Elements_.push_back(D3DElement);
    }
    MIKASA_ASSERT(Elements_.size() == elements.size());
}

DXGI_FORMAT RHIVertexDeclarationDX11::ConvertFormat(VertexElementType type)
{
    switch (type)
    {
        case VertexElementType::VET_Float1:
            return DXGI_FORMAT_R32_FLOAT;
        case VertexElementType::VET_Float2:
            return DXGI_FORMAT_R32G32_FLOAT;
        case VertexElementType::VET_Float3:
            return DXGI_FORMAT_R32G32B32_FLOAT;
        case VertexElementType::VET_Float4:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;
        case VertexElementType::VET_UByte4N:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case VertexElementType::VET_Color:
            return DXGI_FORMAT_B8G8R8A8_UNORM;
        default:
            throw;
    }
}

std::vector<D3D11_INPUT_ELEMENT_DESC> &RHIVertexDeclarationDX11::GetElements()
{
    return Elements_;
}
