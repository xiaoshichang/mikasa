#ifdef MIKASA_TARGET_PLATFORM_Window

#include "RHIIndexBufferDX11.h"

using namespace mikasa::Runtime::Core;

RHIIndexBufferDX11::RHIIndexBufferDX11(ID3D11Device* device, RHIIndexBufferCreateInfo& createInfo)
    : RHIIndexBuffer(createInfo.ElementType)
{
    D3D11_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = createInfo.CpuResourceSize;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = createInfo.CpuResourceAddr;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    if (device->CreateBuffer(&indexBufferDesc, &indexData, &Buffer_) != S_OK)
    {
        throw;
    }
}

RHIIndexBufferDX11::~RHIIndexBufferDX11()
{
    MIKASA_ASSERT(Buffer_ != nullptr);
    Buffer_->Release();
    Buffer_ = nullptr;
}

ID3D11Buffer* RHIIndexBufferDX11::GetInternal() const
{
    return Buffer_;
}

DXGI_FORMAT RHIIndexBufferDX11::GetFormat()
{
    auto elementType = GetElementType();
    if (elementType == IndexBufferElementType::IET_U16)
    {
        return DXGI_FORMAT_R16_UINT;
    }
    else if (elementType == IndexBufferElementType::IET_U32)
    {
        return DXGI_FORMAT_R32_UINT;
    }
    else
    {
        throw;
    }
}

#endif