#pragma once
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    struct RenderViewInfo
    {
        Matrix4x4f ViewMatrix;
        Matrix4x4f ProjectionMatrix;
        Vector4f ClearColor;
    };
}

