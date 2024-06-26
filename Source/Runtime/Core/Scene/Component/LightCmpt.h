#pragma once
#include <memory>
#include "Component.h"
#include "Runtime/Core/Render/Renderer/Light/LightRenderProxy.h"

namespace mikasa::Runtime::Core
{
    class LightCmpt : public Component
    {
    public:
        explicit LightCmpt(GameObject* owner);
        ~LightCmpt() override;

    private:
        void InitRenderThreadPart();
        void UnInitRenderThreadPart();

    private:
        std::shared_ptr<LightRenderProxy> RenderProxy_;

    };
}


