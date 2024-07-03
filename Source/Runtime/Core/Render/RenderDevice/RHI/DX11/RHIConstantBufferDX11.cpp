
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
