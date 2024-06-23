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
        /**
         * create a new game object into this scene.
         * @param name the name of the game object.
         * @param parent the parent of the game object. Add to Roots_ if nullptr.
         */
        GameObject* CreateGameObject(const std::string& name = "GameObject", GameObject* parent = nullptr);

        /**
         * destroy the game object from this scene.
         * @param go the game object to be remove.
         */
        void DestroyGameObject(GameObject* go);


        void LogTotalSceneInfo();
        void LogSingleGameObject(std::string& output, GameObject* go);

        std::shared_ptr<RenderScene> GetRenderScene() { return RenderScene_; }


    private:
        std::vector<GameObject*> Roots_;

        std::shared_ptr<RenderScene> RenderScene_;
    };
}
