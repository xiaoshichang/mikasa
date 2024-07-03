#pragma once

#include "../Transform.h"

namespace mikasa::Runtime::Core
{
    class GameObject;
    class Component
    {
    public:
        explicit Component(GameObject* owner)
        {
            Owner_ = owner;
        }

        virtual ~Component()
        {
            Owner_ = nullptr;
        }

        Transform& GetTransform();

    protected:
        GameObject* Owner_;
    };
}
