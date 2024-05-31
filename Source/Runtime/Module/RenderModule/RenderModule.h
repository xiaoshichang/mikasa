#pragma once

#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Foundation/MultiThread.h"
#include "Runtime/Core/Misc/ApplicationInitParam.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Module
{
    class RenderModule
    {
    public:
        static void Init(const ApplicationInitParam& info);
        static void UnInit();

    private:
        static Runnable* RenderThreadRunnable_;
        static RunnableThread* RenderThread_;

    };
}
