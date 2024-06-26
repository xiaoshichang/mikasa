#pragma once
#include "Component.h"

namespace mikasa::Runtime::Core
{
    enum CameraType
    {
        Orthographic,
        Perspective
    };

    class CameraCmpt : public Component
    {
    public:
        explicit CameraCmpt(GameObject* owner);
        ~CameraCmpt() override;
    };

}
