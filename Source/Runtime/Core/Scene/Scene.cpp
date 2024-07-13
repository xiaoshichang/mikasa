
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
    std::vector<GameObject*> all(GameObjects_);
    for (auto go : all)
    {
        DestroyGameObject(go);
    }
}

GameObject* Scene::CreateGameObject(const std::string &name, GameObject* parent)
{
    auto go = new GameObject(this, name);
    GameObjects_.push_back(go);
    return go;
}

void Scene::DestroyGameObject(GameObject* go)
{
    erase(GameObjects_, go);
    delete go;
}

void Scene::LogTotalSceneInfo()
{
    std::string info = "\n";
    info += std::format("Total GameObject: {}\n", GameObjects_.size());
    info += std::format("Total Cameras :{}\n", Cameras_.size());
    Logger::Info(info.c_str());
}

void Scene::AddCameraToScene(CameraCmpt *camera)
{
    Cameras_.push_back(camera);
}

void Scene::RemoveCameraFromScene(CameraCmpt *camera)
{
    erase(Cameras_, camera);
}

const std::vector<CameraCmpt *>& Scene::GetAllCameras()
{
    return Cameras_;
}

const std::vector<GameObject *> &Scene::GetAllGameObjects()
{
    return GameObjects_;
}

