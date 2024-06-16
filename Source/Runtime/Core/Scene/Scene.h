#pragma once
#include <vector>
#include "GameObject.h"

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
        void LogSingleGameObject(std::string& output, GameObject* go, int indent);


    private:
        std::vector<GameObject*> Roots_;
        int TotalGameObjectCount_ = 0;

    };
}
