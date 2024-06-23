
#include "Scene.h"
#include "Runtime/Foundation/Foundation.h"
#include <format>

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

Scene::Scene()
{
    RenderScene_ = std::make_shared<RenderScene>();
}

Scene::~Scene()
{

}

GameObject* Scene::CreateGameObject(const std::string &name, GameObject* parent)
{
    auto go = new GameObject(name);
    Roots_.push_back(go);
    return go;
}

void Scene::DestroyGameObject(GameObject* go)
{
    erase(Roots_, go);
    delete go;
}



void Scene::LogTotalSceneInfo()
{
    std::string info = "\n";
    info += std::format("Total GameObject: {}\n", Roots_.size());
    for (auto item : Roots_)
    {
        LogSingleGameObject(info, item);
    }

    Logger::Info(info.c_str());
}

void Scene::LogSingleGameObject(std::string& output, GameObject *go)
{
    output += std::format("{}\n", go->Name_);
}

