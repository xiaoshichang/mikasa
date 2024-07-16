
#include "RHITexture.h"

using namespace mikasa::Runtime::Core;

RHITexture::RHITexture()
{

}

RHITexture::~RHITexture()
{

}

RHIRenderTargetView *RHITexture::AsRenderTarget()
{
    MIKASA_ASSERT(RenderTargetView_ != nullptr);
    return RenderTargetView_;
}

RHIShaderResourceView *RHITexture::AsRHIShaderResourceView()
{
    MIKASA_ASSERT(ShaderResourceView_ != nullptr);
    return ShaderResourceView_;
}

RHIDepthStencilView *RHITexture::AsDepthStencil()
{
    MIKASA_ASSERT(DepthStencilView_ != nullptr);
    return DepthStencilView_;
}


