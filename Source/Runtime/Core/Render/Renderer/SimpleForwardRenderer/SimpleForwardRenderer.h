#pragma once
#include "../Renderer.h"

namespace mikasa::Runtime::Core
{
    class SimpleForwardRenderer : public Renderer
    {
    public:
        explicit SimpleForwardRenderer(const std::shared_ptr<RenderViewInfo>& vf);

        ~SimpleForwardRenderer() override = default;
        void Render() override;

    };

}
