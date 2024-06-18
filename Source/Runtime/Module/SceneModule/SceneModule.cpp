
#include "SceneModule.h"
#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Core/Render/RenderCommand/RenderCommandQueue.h"


using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Foundation;

Scene* SceneModule::Current = nullptr;

static int frameCount = 0;
static int logicCount = 0;

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
    auto light = scene->CreateGameObject("light");
    auto camera = scene->CreateGameObject("camera");
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
    Logger::Info("logic frame %d", logicCount);
    logicCount ++;
}

void SceneModule::Render()
{
    auto lambda = []()
    {
        Logger::Info("render frame %d", frameCount);
        frameCount ++;
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}


