
#include "GameViewClient.h"
#include "Runtime/Framework/Application/Application.h"
#include "Runtime/Module/SceneModule/SceneModule.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include "Runtime/Core/Render/Renderer/SimpleForwardRenderer/SimpleForwardRenderer.h"
#include "Runtime/Core/Render/RenderDevice/RenderResource/RenderTarget.h"

using namespace mikasa::Runtime::Framework;
using namespace mikasa::Runtime::Module;

std::shared_ptr<RenderTarget> GameViewClient::SceneColorRT = nullptr;

void GameViewClient::Init()
{
    RenderTextureDesc desc{};
    desc.Format = PixelFormat::PF_R8G8B8A8_UNorm;

    if (Application::Param.EditorMode)
    {
        desc.Width = 1024;
        desc.Height = 768;
    }
    else
    {
        desc.Width = Application::Param.WindowWidth;
        desc.Height = Application::Param.WindowHeight;
    }

    desc.Flag |= RHITextureCreateFlag::TCF_AsRenderTarget;
    desc.Flag |= RHITextureCreateFlag::TCF_AsShaderResource;

    SceneColorRT = std::make_shared<RenderTarget>(desc);
    auto rt = SceneColorRT;
    auto lambda = [=] ()
    {
        rt->InitRHIResource();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

void GameViewClient::UnInit()
{
    SceneColorRT.reset();
}

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
    rvfi.RenderTarget = SceneColorRT;
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
    RenderViewInitializer initializer;
    initializer.Camera = *camera->GetCamera();
    initializer.ViewMatrix = camera->GetViewMatrix();
    initializer.ProjectionMatrix = camera->GetCamera()->GetProjectionMatrix();
    return std::make_shared<RenderView>(initializer);
}

std::shared_ptr<RenderTarget> &GameViewClient::GetSceneColorRT()
{
    return SceneColorRT;
}


