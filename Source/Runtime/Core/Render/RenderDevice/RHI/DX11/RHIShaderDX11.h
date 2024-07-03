#pragma once
#include "../RHIShader.h"
#include "Runtime/Foundation/Foundation.h"
#include <memory>
#include <d3d11.h>

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class RHIVertexShaderDX11 : public RHIVertexShader
    {
    public:
        explicit RHIVertexShaderDX11(ID3D11Device* device, const ShaderByteCodeBlob& blob);
        explicit RHIVertexShaderDX11(ID3D11Device* device, const boost::filesystem::path& fp);

        ~RHIVertexShaderDX11() override;
        ID3D11VertexShader* GetInternal();
        const void* GetByteCode() ;
        uint32 GetByteCodeSize() const;

    private:
        ID3D11VertexShader* Internal_ = nullptr;
        ShaderByteCodeBlob BlobFromOutside_ {};
        ID3DBlob* BlobFromPath_ = nullptr;
    };

    class RHIPixelShaderDX11 : public RHIPixelShader
    {
    public:
        explicit RHIPixelShaderDX11(ID3D11Device *device, const ShaderByteCodeBlob& blob);
        explicit RHIPixelShaderDX11(ID3D11Device *device, const boost::filesystem::path& fp);

        ~RHIPixelShaderDX11() override;
        ID3D11PixelShader* GetInternal();

    private:
        ID3D11PixelShader* Internal_ = nullptr;
        ShaderByteCodeBlob BlobFromOutside_ = {};
        ID3DBlob* BlobFromPath_ = nullptr;
    };
}

