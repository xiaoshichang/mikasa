#ifdef MIKASA_TARGET_PLATFORM_Window
#include "RHIVertexBufferDX11.h"

using namespace mikasa::Runtime::Core;

RHIVertexBufferDX11::RHIVertexBufferDX11(ID3D11Device *device, RHIVertexBufferCreateInfo& createInfo)
{
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = createInfo.CpuResourceSize;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = createInfo.CpuResourceAddr;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    if (device->CreateBuffer(&bd, &vertexData, &Buffer_) != S_OK)
    {
        throw;
    }

    createInfo.DiscardCpuResourceAfterCreateRHIResource();
}

RHIVertexBufferDX11::~RHIVertexBufferDX11()
{
    MIKASA_ASSERT(Buffer_ != nullptr);
    Buffer_->Release();
    Buffer_ = nullptr;
}

ID3D11Buffer *RHIVertexBufferDX11::GetInternal() const
{
    return Buffer_;
}

#endif