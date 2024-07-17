
#include "RenderTexture.h"
#include "../RenderDevice.h"

using namespace mikasa::Runtime::Core;

RenderTexture::RenderTexture(const RenderTextureDesc& desc)
    : Desc_(desc)
{
}

void RenderTexture::InitRHIResource()
{
    RHITextureCreateInfo info{};
    info.Desc.Width = Desc_.Width;
    info.Desc.Height = Desc_.Height;
    info.Desc.Format = Desc_.Format;
    info.Flag = Desc_.Flag;
    RHITexture_ = RenderDevice::RHI->CreateRHITexture(info);
}

RHIRenderTargetView* RenderTexture::AsRenderTargetView()
{
    return RHITexture_->AsRenderTarget();
}

RHIShaderResourceView *RenderTexture::AsShaderResourceView()
{
    return RHITexture_->AsShaderResourceView();
}


std::shared_ptr<RHITexture> &RenderTexture::GetRHITexture()
{
    return RHITexture_;
}



