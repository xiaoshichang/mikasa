#pragma once
#include "RenderTexture.h"
#include <memory>
#include <unordered_map>

namespace mikasa::Runtime::Core
{
    class RenderTexturePool
    {
    public:
        static std::shared_ptr<RenderTexture> FindOrCreate(const RenderTextureDesc& desc);

    private:
        static std::unordered_map<int, std::shared_ptr<RenderTexture>> PooledRenderTexture_;
    };
}