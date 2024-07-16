#pragma once
#include "RenderResource.h"
#include "Runtime/Core/Render/RenderDevice/RHI/RHICommon.h"
#include "Runtime/Core/Render/RenderDevice/RHI/RHITexture.h"

namespace mikasa::Runtime::Core
{
    struct RenderTextureDesc
    {
        int Width;
        int Height;
        PixelFormat Format;
        uint64 Flag;
    };

    class RenderTexture  : public RenderResource
    {
    public:
        explicit RenderTexture(const RenderTextureDesc& desc);
        ~RenderTexture() override = default;
        void InitRHIResource() override;
        RHIRenderTargetView* AsRHIRenderTargetView();
        std::shared_ptr<RHITexture>& GetRHITexture();


    private:
        RenderTextureDesc Desc_;
        std::shared_ptr<RHITexture> RHITexture_;
    };
}

