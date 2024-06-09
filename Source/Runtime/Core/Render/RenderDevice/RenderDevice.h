#pragma once
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"

namespace mikasa::Runtime::Core
{
    class RHI;
    class RenderDevice
    {
    public:
        static void Init(const ApplicationInitParam& param, const WindowHandler& windowHandler);
        static void UnInit();

    private:
        static RHI* RHI_;
    };
}

