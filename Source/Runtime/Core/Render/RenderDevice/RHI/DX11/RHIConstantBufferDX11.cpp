#ifdef MIKASA_TARGET_PLATFORM_Window

#include "RHIConstantBufferDX11.h"

using namespace mikasa::Runtime::Core;

RHIConstantBufferDX11::RHIConstantBufferDX11(ID3D11Device* device, RHIConstantBufferCreateInfo &createInfo)
{
    D3D11_BUFFER_DESC Desc;
    Desc.ByteWidth = createInfo.CpuResourceSize;
    Desc.Usage = D3D11_USAGE_DYNAMIC;
    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    Desc.MiscFlags = 0;
    Desc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA initData;
    initData.pSysMem = createInfo.CpuResourceAddr;
    initData.SysMemPitch = initData.SysMemSlicePitch = 0;

    if (device->CreateBuffer(&Desc, &initData, &Buffer_) != S_OK)
    {
        throw;
    }
}

RHIConstantBufferDX11::~RHIConstantBufferDX11()
{
    MIKASA_ASSERT(Buffer_ != nullptr);
    Buffer_->Release();
    Buffer_ = nullptr;
}

ID3D11Buffer *RHIConstantBufferDX11::GetInternal() const
{
    return Buffer_;
}

void RHIConstantBufferDX11::UpdateGpuBuffer(ID3D11DeviceContext* context, uint8* data, uint32 size)
{
    MIKASA_ASSERT(size % 16 == 0);

    D3D11_MAPPED_SUBRESOURCE MappedSubresource;
    if (context->Map(Buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedSubresource) != S_OK)
    {
        MIKASA_ASSERT(false);
        throw;
    }
    memcpy_s(MappedSubresource.pData, size, data, size);
    context->Unmap(Buffer_, 0);
}

#endif