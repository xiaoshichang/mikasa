#ifdef MIKASA_TARGET_PLATFORM_Window

#include "RHIShaderDX11.h"
#include <d3dcompiler.h>

using namespace mikasa::Runtime::Core;

RHIVertexShaderDX11::RHIVertexShaderDX11(ID3D11Device *device, const ShaderByteCodeBlob& blob)
{
    BlobFromOutside_ = blob;
    auto hr = device->CreateVertexShader(BlobFromOutside_.ByteCode, BlobFromOutside_.ByteCodeSize, nullptr, &Internal_);
    if (hr != S_OK)
    {
        throw;
    }
}

RHIVertexShaderDX11::RHIVertexShaderDX11(ID3D11Device *device, const boost::filesystem::path& fp)
{

    ID3D10Blob* errorMessage;

    DWORD dwShaderFlags = 0;
#if MIKASA_BUILDTYPE_DEBUG
    dwShaderFlags |= D3DCOMPILE_ENABLE_STRICTNESS;
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    auto ret = D3DCompileFromFile(fp.c_str(),
                                  nullptr,
                                  D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                  "main",
                                  "vs_5_0",
                                  dwShaderFlags,
                                  0,
                                  &BlobFromPath_,
                                  &errorMessage);

    if (ret != S_OK)
    {
        OutputDebugStringA(reinterpret_cast<const char*>(errorMessage->GetBufferPointer()));
        auto message = reinterpret_cast<const char*>(errorMessage->GetBufferPointer());
        Logger::Error(message);
        throw;
    }

    auto hr = device->CreateVertexShader(BlobFromPath_->GetBufferPointer(),
                                         BlobFromPath_->GetBufferSize(),
                                         nullptr,
                                         &Internal_);
    if (hr != S_OK)
    {
        throw;
    }
}

RHIVertexShaderDX11::~RHIVertexShaderDX11()
{
    Internal_->Release();
    Internal_ = nullptr;

    if (BlobFromPath_ != nullptr)
    {
        BlobFromPath_->Release();
        BlobFromPath_ = nullptr;
    }
    else
    {
        delete BlobFromOutside_.ByteCode;
        BlobFromOutside_.ByteCode = nullptr;
    }
}

ID3D11VertexShader *RHIVertexShaderDX11::GetInternal()
{
    return Internal_;
}

const void* RHIVertexShaderDX11::GetByteCode()
{
    if (BlobFromPath_ != nullptr)
    {
        return BlobFromPath_->GetBufferPointer();
    }
    else
    {
        return BlobFromOutside_.ByteCode;
    }
}

uint32 RHIVertexShaderDX11::GetByteCodeSize() const
{
    if (BlobFromPath_ != nullptr)
    {
        return BlobFromPath_->GetBufferSize();
    }
    else
    {
        return BlobFromOutside_.ByteCodeSize;
    }
}


RHIPixelShaderDX11::RHIPixelShaderDX11(ID3D11Device *device, const ShaderByteCodeBlob& blob)
{
    BlobFromOutside_ = blob;
    auto hr = device->CreatePixelShader(BlobFromOutside_.ByteCode, BlobFromOutside_.ByteCodeSize, nullptr, &Internal_);
    if (hr != S_OK)
    {
        throw;
    }

}

RHIPixelShaderDX11::RHIPixelShaderDX11(ID3D11Device *device, const boost::filesystem::path& fp)
{
    ID3D10Blob* errorMessage;

    DWORD dwShaderFlags = 0;
#if MIKASA_BUILDTYPE_DEBUG
    dwShaderFlags |= D3DCOMPILE_ENABLE_STRICTNESS;
    dwShaderFlags |= D3DCOMPILE_DEBUG;
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    if (D3DCompileFromFile(fp.c_str(),
                           nullptr,
                           D3D_COMPILE_STANDARD_FILE_INCLUDE,
                           "main",
                           "ps_5_0",
                           dwShaderFlags,
                           0,
                           &BlobFromPath_,
                           &errorMessage) != S_OK)
    {
        OutputDebugStringA(reinterpret_cast<const char*>(errorMessage->GetBufferPointer()));
        auto message = reinterpret_cast<const char*>(errorMessage->GetBufferPointer());
        Logger::Error(message);
        throw;
    }

    auto hr = device->CreatePixelShader(BlobFromPath_->GetBufferPointer(),
                                         BlobFromPath_->GetBufferSize(),
                                         nullptr,
                                         &Internal_);
    if (hr != S_OK)
    {
        throw;
    }
}


RHIPixelShaderDX11::~RHIPixelShaderDX11()
{
    Internal_->Release();
    Internal_ = nullptr;

    if (BlobFromPath_ != nullptr)
    {
        BlobFromPath_->Release();
        BlobFromPath_ = nullptr;
    }
    else
    {
        delete BlobFromOutside_.ByteCode;
        BlobFromOutside_.ByteCode = nullptr;
    }
}

ID3D11PixelShader *RHIPixelShaderDX11::GetInternal()
{
    return Internal_;
}


#endif