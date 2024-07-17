
#include "RHITextureDX11.h"
#include "RHIRenderTargetViewDX11.h"
#include "RHIShaderResourceViewDX11.h"
#include "RHIUtilsDX11.h"

using namespace mikasa::Runtime::Core;

RHITextureDX11::RHITextureDX11(ID3D11Device* device, const RHITextureCreateInfo& createInfo)
{
    bool asRenderTarget = createInfo.Flag & RHITextureCreateFlag::TCF_AsRenderTarget;
    bool asShaderResource = createInfo.Flag & RHITextureCreateFlag::TCF_AsShaderResource;
    bool asDepthStencil = createInfo.Flag & RHITextureCreateFlag::TCP_AsDepthStencil;

    D3D11_TEXTURE2D_DESC resDesc = {};
    resDesc.Width = createInfo.Desc.Width;
    resDesc.Height = createInfo.Desc.Height;
    resDesc.MipLevels = 1;
    resDesc.ArraySize = 1;
    resDesc.Format = RHIUtilsDX11::ConvertPixelFormat(createInfo.Desc.Format);
    resDesc.SampleDesc.Count = 1;
    resDesc.Usage = D3D11_USAGE_DEFAULT;
    resDesc.BindFlags = 0;
    if (asRenderTarget) resDesc.BindFlags |= D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET;
    if (asShaderResource) resDesc.BindFlags |= D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
    if (asDepthStencil)  resDesc.BindFlags |= D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
    if (device->CreateTexture2D(&resDesc, nullptr, reinterpret_cast<ID3D11Texture2D **>(&Resource_)) != S_OK)
    {
        MIKASA_ASSERT(false);
    }

    if (asRenderTarget)
    {
        RenderTargetView_ = new RHIRenderTargetViewDX11(device, Resource_);
    }

    if (asShaderResource)
    {
        ShaderResourceView_ = new RHIShaderResourceViewDX11(device, Resource_);
    }
}

RHITextureDX11::RHITextureDX11(ID3D11Device* device, ID3D11Resource* backBuffer)
{
    Resource_ = backBuffer;
    RenderTargetView_ = new RHIRenderTargetViewDX11(device, backBuffer);
}

RHITextureDX11::~RHITextureDX11()
{
    if (RenderTargetView_ != nullptr)
    {
        delete RenderTargetView_;
    }

}

ID3D11Resource *RHITextureDX11::GetInternalResource()
{
    return Resource_;
}




