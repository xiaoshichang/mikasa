#pragma once
#include "RenderTexture.h"
#include <memory>
#include <unordered_map>

namespace mikasa::Runtime::Core
{


    class RenderTarget : public RenderTexture
    {
    public:
        explicit RenderTarget(const RenderTextureDesc& desc);
        ~RenderTarget() override = default;

    };

}

