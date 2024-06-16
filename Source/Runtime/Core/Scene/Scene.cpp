
#include "Scene.h"
#include "Runtime/Foundation/Foundation.h"
#include <format>

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

Scene::Scene()
{

}

Scene::~Scene()
{

}

GameObject* Scene::CreateGameObject(const std::string &name, GameObject* parent)
{
    auto go = new GameObject(this, name);
    TotalGameObjectCount_ += 1;
    if (parent == nullptr)
    {
        Roots_.push_back(go);
    }
    else
    {
        parent->AddChild(go);
        go->SetParent(parent);
    }
    return go;
}

void Scene::DestroyGameObject(GameObject* go)
{
    auto parent = go->Parent_;

    if (parent == nullptr)
    {
        erase(Roots_, go);
    }

    for (auto child : go->Children_)
    {
        DestroyGameObject(child);
    }
    delete go;
    TotalGameObjectCount_ -= 1;
}



void Scene::LogTotalSceneInfo()
{
    std::string info = "\n";
    info += std::format("Total GameObject: {}\n", TotalGameObjectCount_);
    for (auto item : Roots_)
    {
        LogSingleGameObject(info, item, 0);
    }


    Logger::Info(info.c_str());
}

void Scene::LogSingleGameObject(std::string& output, GameObject *go, int indent)
{
    for(int i = 0; i < indent; i++)
    {
        output += '\t';
    }
    output += std::format("{}\n", go->Name_);

    for(auto child : go->Children_)
    {
        LogSingleGameObject(output, child, indent + 1);
    }
}

