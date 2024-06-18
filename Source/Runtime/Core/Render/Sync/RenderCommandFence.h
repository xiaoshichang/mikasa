#pragma once
#include "Runtime/Foundation/MultiThread.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class RenderCommandFence
    {
    public:
        RenderCommandFence();
    public:
        void BeginFence();
        void Wait();

    private:
        ManualResetEvent Event_;
    };
}

