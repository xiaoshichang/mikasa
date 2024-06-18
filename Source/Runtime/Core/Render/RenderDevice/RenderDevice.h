#pragma once
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"
#include "Runtime/Core/Render/RenderCommand/RenderCommandBase.h"





namespace mikasa::Runtime::Core
{
    class RHI;
    class RenderDevice
    {
    public:
        static void Init(const ApplicationInitParam& param, const WindowHandler& windowHandler);
        static void UnInit();
        static bool ProcessOneRenderCommand();
        static void FlushAllRenderCommand();

    private:
        static RHI* RHI_;
    };
}

