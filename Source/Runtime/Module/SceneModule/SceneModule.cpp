
#include "SceneModule.h"
#include "Runtime/Foundation/Foundation.h"

#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"
#include "Runtime/Core/Render/Renderer/SimpleForwardRenderer/SimpleForwardRenderer.h"

using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Foundation;

Scene* SceneModule::Current = nullptr;


void SceneModule::Init()
{

}

void SceneModule::UnInit()
{
    if (Current != nullptr)
    {
        DestroyCurrentScene();
    }
}

void SceneModule::SyncLoadScene(const std::string& path)
{
    if (Current != nullptr)
    {
        DestroyCurrentScene();
    }
    DoSyncLoadScene(path);
}

void SceneModule::DoSyncLoadScene(const std::string &path)
{
    auto scene = new Scene();
    auto cube = scene->CreateGameObject("cube");
    cube->InitStaticMeshRenderCmpt();

    auto light = scene->CreateGameObject("light");
    light->InitLightCmpt();

    auto camera = scene->CreateGameObject("camera");
    camera->InitCameraCmpt();

    Current = scene;
}

void SceneModule::DestroyCurrentScene()
{
    MIKASA_ASSERT(Current != nullptr);
    delete Current;
    Current = nullptr;
}

void SceneModule::Update()
{
}

void SceneModule::Render()
{
    auto scene = Current->GetRenderScene();
    auto vf = Current->GetMainCamera()->CreateRenderViewInfo();
    auto renderer = new SimpleForwardRenderer(scene, vf, RenderDevice::RHI->GetBackBufferRTV());

    auto lambda = [renderer]()
    {
        renderer->Render();
        delete renderer;
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}


