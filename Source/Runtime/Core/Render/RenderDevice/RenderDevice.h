#pragma once
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"
#include "Runtime/Core/Render/RenderCommand/RenderCommandBase.h"
#include "../RHI/RHI.h"

namespace mikasa::Runtime::Core
{
    class RenderDevice
    {
    public:
        static void Init(const ApplicationInitParam& param, const WindowHandler& windowHandler);
        static void UnInit();
        static bool ProcessOneRenderCommand();
        static void FlushAllRenderCommand();

    public:
        static RHI* RHI;
    };
}

