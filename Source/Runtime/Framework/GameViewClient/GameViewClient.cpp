
#include "GameViewClient.h"
#include "Runtime/Module/SceneModule/SceneModule.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include "Runtime/Core/Render/Renderer/SimpleForwardRenderer/SimpleForwardRenderer.h"

using namespace mikasa::Runtime::Framework;
using namespace mikasa::Runtime::Module;

void GameViewClient::Render()
{
    auto scene = SceneModule::Current->GetRenderScene();
    auto viewFamily = BuildRenderViewFamily();

    auto renderer = new SimpleForwardRenderer(scene, viewFamily);
    auto lambda = [renderer]()
    {
        renderer->Render();
        delete renderer;
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

std::shared_ptr<RenderViewFamily> GameViewClient::BuildRenderViewFamily()
{
    auto scene = SceneModule::Current->GetRenderScene();
    RenderViewFamilyInitializer rvfi;
    rvfi.RenderTarget = RenderDevice::RHI->GetBackBufferRTV();
    rvfi.ClearColor = Vector4f(0.2, 0.3, 0.4, 1.0);

    for (auto camera : SceneModule::Current->GetAllCameras())
    {
        auto view = BuildRenderView(camera);
        if (view != nullptr)
        {
            rvfi.Views.push_back(view);
        }
    }

    // todo: support multi camera
    MIKASA_ASSERT(rvfi.Views.size() == 1);

    return std::make_shared<RenderViewFamily>(rvfi);
}

std::shared_ptr<RenderView> GameViewClient::BuildRenderView(CameraCmpt *camera)
{
    RenderViewInitializer initializer{};
    initializer.CameraCmpt = camera;
    return std::make_shared<RenderView>(initializer);
}
