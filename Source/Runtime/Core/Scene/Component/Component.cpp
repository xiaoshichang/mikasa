
#include "Component.h"
#include "../GameObject.h"

using namespace mikasa::Runtime::Core;

Transform& Component::GetTransform()
{
    return Owner_->GetTransform();
}
