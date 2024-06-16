#pragma once
#include <string>
#include <vector>

namespace mikasa::Runtime::Core
{
    class Scene;
    class GameObject
    {
    private:
        explicit GameObject(Scene* scene, std::string  name);
        ~GameObject();

    private:
        bool AddChild(GameObject* child);
        void SetParent(GameObject* parent);
        GameObject* GetParent();

    private:
        GameObject* Parent_ = nullptr;
        std::vector<GameObject*> Children_;

    public:
        friend class Scene;

    private:
        std::string Name_;
        Scene* Scene_ = nullptr;
    };
}


