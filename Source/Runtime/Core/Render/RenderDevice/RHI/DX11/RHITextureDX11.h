#pragma once

#include "../RHITexture.h"
#include <d3d11.h>

namespace mikasa::Runtime::Core
{
    class RHITextureDX11 : public RHITexture
    {
    public:

        /**
         * create a texture from description
         */
        explicit RHITextureDX11(ID3D11Device* device, const RHITextureCreateInfo& createInfo);

        /**
         * create a texture to represents rhi back-buffer
         */
        explicit RHITextureDX11(ID3D11Device* device, ID3D11Resource* backBuffer);

        ~RHITextureDX11() override;

        ID3D11Resource* GetInternalResource();

    private:
        ID3D11Resource* Resource_ = nullptr;
    };

}
