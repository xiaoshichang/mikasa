#pragma once
#include "RHIResource.h"
#include "RHICommon.h"
#include "RHIShaderResourceView.h"
#include "RHIRenderTargetView.h"
#include "RHIDepthStencilView.h"

namespace mikasa::Runtime::Core
{
    struct RHITextureDesc
    {
        int Width;
        int Height;
        PixelFormat Format;
    };

    enum RHITextureCreateFlag : uint64
    {
        TCF_None = 0,
        TCF_AsRenderTarget =        1 << 0,
        TCF_AsShaderResource =      1 << 1,
        TCP_AsDepthStencil =        2 << 2,
    };

    struct RHITextureCreateInfo
    {
        RHITextureDesc Desc;
        uint64 Flag;
    };


    class RHITexture : public RHIResource
    {
    public:
        explicit RHITexture();
        ~RHITexture() override;

        RHIRenderTargetView* AsRenderTarget();
        RHIShaderResourceView* AsRHIShaderResourceView();
        RHIDepthStencilView* AsDepthStencil();

    protected:
        RHIRenderTargetView* RenderTargetView_ = nullptr;
        RHIShaderResourceView* ShaderResourceView_ = nullptr;
        RHIDepthStencilView* DepthStencilView_ = nullptr;
    };
}

