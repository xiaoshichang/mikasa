#pragma once
#include <memory>
#include "RenderViewInfo.h"
#include "RenderScene.h"


namespace mikasa::Runtime::Core
{

    class Renderer
    {
    public:
        explicit Renderer(const std::shared_ptr<RenderScene>& scene,  const std::shared_ptr<RenderViewInfo>& vf);
        virtual ~Renderer();
        virtual void Render() = 0;

    protected:
         std::shared_ptr<RenderViewInfo> ViewInfo_;
         std::shared_ptr<RenderScene> RenderScene_;
    };
}
