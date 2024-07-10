#ifdef MIKASA_TARGET_PLATFORM_Window
#pragma once
#include "../RHIBoundShaderState.h"
#include "RHIVertexDeclarationDX11.h"
#include "RHIShaderDX11.h"

#include <memory>

namespace mikasa::Runtime::Core
{
    class RHIBoundShaderStateDX11 : public RHIBoundShaderState
    {
    public:
        RHIBoundShaderStateDX11(ID3D11Device *device,
                                const std::shared_ptr<RHIVertexDeclaration>& vd,
                                const std::shared_ptr<RHIVertexShader>& vs,
                                const std::shared_ptr<RHIPixelShader>& ps);

        ~RHIBoundShaderStateDX11() override;

        void Bind(ID3D11DeviceContext *context);

    private:
        ID3D11InputLayout* InputLayout_ = nullptr;
        std::shared_ptr<RHIVertexShaderDX11> VertexShader_;
        std::shared_ptr<RHIPixelShaderDX11> PixelShader_;
    };
}
#endif