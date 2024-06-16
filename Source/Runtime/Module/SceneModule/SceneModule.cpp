#include "Runtime/Foundation/Foundation.h"
#include "SceneModule.h"

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


