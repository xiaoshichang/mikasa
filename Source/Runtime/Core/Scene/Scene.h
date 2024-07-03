#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Runtime/Core/Render/Renderer/RenderScene.h"

namespace mikasa::Runtime::Core
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

    public:

        GameObject* CreateGameObject(const std::string& name = "GameObject", GameObject* parent = nullptr);
        void DestroyGameObject(GameObject* go);

        void AddCameraToScene(CameraCmpt* camera);
        void RemoveCameraFromScene(CameraCmpt* camera);

        const std::vector<CameraCmpt*>& GetAllCameras();

        std::shared_ptr<RenderScene> GetRenderScene() { return RenderScene_; }

        void LogTotalSceneInfo();


    private:
        std::vector<GameObject*> Roots_;
        std::vector<CameraCmpt*> Cameras_;

        std::shared_ptr<RenderScene> RenderScene_;
    };
}
