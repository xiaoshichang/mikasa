#pragma once
#include "Runtime/Core/Render/Renderer/Mesh/StaticMeshRenderProxy.h"
#include "Component.h"
#include <memory>

namespace mikasa::Runtime::Core
{
    class StaticMeshRenderCmpt : public Component
    {
    public:
        explicit StaticMeshRenderCmpt(GameObject* owner);
        ~StaticMeshRenderCmpt() override;

    private:
        void InitRenderThreadPart();
        void UnInitRenderThreadPart();

    private:

        std::shared_ptr<StaticMeshRenderProxy> RenderProxy_;
    };

}
