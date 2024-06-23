#pragma once
#include <memory>
#include "RenderViewInfo.h"


namespace mikasa::Runtime::Core
{

    class Renderer
    {
    public:
        explicit Renderer(const std::shared_ptr<RenderViewInfo>& vf);
        virtual ~Renderer();
        virtual void Render() = 0;

    protected:
         std::shared_ptr<RenderViewInfo> ViewInfo_;
    };
}
