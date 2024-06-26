#pragma once

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

    protected:
        GameObject* Owner_;
    };
}
