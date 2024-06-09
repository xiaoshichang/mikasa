#pragma once

#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Foundation/MultiThread.h"
#include "Runtime/Core/Misc/ApplicationInitParam.h"
#include "Runtime/Core/Misc/WindowHandler.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class RenderCommandQueue;
    class RenderDevice;
}

namespace mikasa::Runtime::Module
{

    class RenderModule
    {
    public:
        static void Init(const ApplicationInitParam& param, const WindowHandler& windowHandler);
        static void UnInit();

    private:
        static Runnable* RenderThreadRunnable_;
        static RunnableThread* RenderThread_;
        static RenderCommandQueue* RenderCommandQueue_;

    };
}
