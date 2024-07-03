#pragma once

#include "../RHIVertexDeclaration.h"
#include <d3d11.h>


namespace mikasa::Runtime::Core
{

    class RHIVertexDeclarationDX11 : public RHIVertexDeclaration
    {
    public:
        explicit RHIVertexDeclarationDX11(const std::vector<VertexDeclarationElement> &elements);
        std::vector<D3D11_INPUT_ELEMENT_DESC>& GetElements();

    private:
        static DXGI_FORMAT ConvertFormat(VertexElementType type);

    private:
        std::vector<D3D11_INPUT_ELEMENT_DESC> Elements_;
    };
}

