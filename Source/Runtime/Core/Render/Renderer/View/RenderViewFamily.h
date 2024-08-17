#pragma once
#include <vector>
#include <memory>
#include "Runtime/Core/Render/RenderDevice/RHI/RHI.h"
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class RenderView;
    class RenderTarget;

    struct RenderViewFamilyInitializer
    {
        std::vector<std::shared_ptr<RenderView>> Views;
        std::shared_ptr<RenderTarget> RenderTarget;
        Vector4f ClearColor;
    };

    /**
     * contains a set of RenderView which only have different view transforms.
     * construct on main thread and copy to render thread.
     */
    class RenderViewFamily
    {
    public:
        explicit RenderViewFamily(const RenderViewFamilyInitializer& initializer);
        ~RenderViewFamily();
        void InitRHIResource();

    public:
        std::vector<std::shared_ptr<RenderView>> Views;
        std::shared_ptr<RenderTarget> RenderTarget;
        Vector4f ClearColor;




    };
}

