#pragma once
#include <memory>
#include "Runtime/Core/Render/Renderer/View/RenderViewFamily.h"
#include "Runtime/Core/Scene/Component/CameraCmpt.h"

using namespace mikasa::Runtime::Core;

namespace mikasa::Runtime::Framework
{
    class GameViewClient
    {
    public:
        static void Init();
        static void UnInit();

        static void Render();
        static std::shared_ptr<RenderTarget>& GetSceneColorRT();


    private:
        static std::shared_ptr<RenderViewFamily> BuildRenderViewFamily();
        static std::shared_ptr<RenderView> BuildRenderView(CameraCmpt* camera);

    private:
        static std::shared_ptr<RenderTarget> SceneColorRT;

    };

}


