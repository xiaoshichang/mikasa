#pragma once
#include "../Renderer.h"

namespace mikasa::Runtime::Core
{
    class SimpleForwardRenderer : public Renderer
    {
    public:
        explicit SimpleForwardRenderer(const std::shared_ptr<RenderScene>& scene, const std::shared_ptr<RenderViewFamily>& vf);
        ~SimpleForwardRenderer() override;
        void RenderSingleView(const std::shared_ptr<RenderView>& view) override;

    };

}
