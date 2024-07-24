#pragma once
#include <memory>
#include "RenderScene.h"
#include "View/RenderViewFamily.h"
#include "View/RenderView.h"

namespace mikasa::Runtime::Core
{


    class Renderer
    {
    public:
        explicit Renderer(const std::shared_ptr<RenderScene>& scene, const std::shared_ptr<RenderViewFamily>& rvf);
        virtual ~Renderer();
        virtual void RenderSingleView(const std::shared_ptr<RenderView>& view) = 0;
        void Render();


    protected:
         std::shared_ptr<RenderViewFamily> ViewFamily_;
         std::shared_ptr<RenderScene> RenderScene_;
    };
}
