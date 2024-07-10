#ifdef MIKASA_TARGET_PLATFORM_Window

#include "RHIBoundShaderStateDX11.h"

using namespace mikasa::Runtime::Core;

RHIBoundShaderStateDX11::RHIBoundShaderStateDX11(ID3D11Device *device,
                                                 const std::shared_ptr<RHIVertexDeclaration>& vd,
                                                 const std::shared_ptr<RHIVertexShader>& vs,
                                                 const std::shared_ptr<RHIPixelShader>& ps)
{
    VertexShader_ = std::dynamic_pointer_cast<RHIVertexShaderDX11>(vs);
    PixelShader_ = std::dynamic_pointer_cast<RHIPixelShaderDX11>(ps);

    auto declaration = (RHIVertexDeclarationDX11*)vd.get();
    auto descArray = declaration->GetElements();
    MIKASA_ASSERT(!descArray.empty());
    auto descAddr = &descArray[0];

    auto vsCode = VertexShader_->GetByteCode();
    auto vsCodeSize = VertexShader_->GetByteCodeSize();

    auto hr = device->CreateInputLayout(descAddr,
                                        descArray.size(),
                                        (const void*)vsCode,
                                        vsCodeSize,
                                        &InputLayout_);
    if (hr != S_OK)
    {
        throw;
    }
}

RHIBoundShaderStateDX11::~RHIBoundShaderStateDX11()
{
    InputLayout_->Release();
    InputLayout_ = nullptr;
    VertexShader_.reset();
    PixelShader_.reset();
}

void RHIBoundShaderStateDX11::Bind(ID3D11DeviceContext *context)
{
    context->IASetInputLayout(InputLayout_);
    context->VSSetShader(VertexShader_->GetInternal(), nullptr, 0);
    context->PSSetShader(PixelShader_->GetInternal(), nullptr, 0);
}

#endif
