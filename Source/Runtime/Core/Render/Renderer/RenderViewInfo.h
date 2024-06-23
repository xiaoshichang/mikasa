#pragma once
#include "Runtime/Foundation/Foundation.h"
#include "../RHI/RHIRenderTargetView.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    struct RenderViewInfo
    {
        Vector3f CameraPosition;
        Vector3f EyePosition;
        float Far;
        float Near;
        Vector4f ClearColor;


        RHIRenderTargetView* Destination;
    };
}

