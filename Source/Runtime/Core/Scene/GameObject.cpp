
#include "GameObject.h"

#include <utility>
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

GameObject::GameObject(Scene* scene, std::string  name)
    : Scene_(scene)
    , Name_(std::move(name))
{
}

GameObject::~GameObject()
{
    MIKASA_ASSERT(Children_.empty());
}


bool GameObject::AddChild(GameObject *child)
{
    if (std::find(Children_.begin(), Children_.end(), child) != Children_.end())
    {
        return false;
    }
    Children_.push_back(child);
    child->SetParent(this);
    return true;
}

void GameObject::SetParent(GameObject *parent)
{
    Parent_ = parent;
}

GameObject *GameObject::GetParent()
{
    return Parent_;
}

