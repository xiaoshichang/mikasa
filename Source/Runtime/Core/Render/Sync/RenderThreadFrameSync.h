#pragma once
#include "Runtime/Foundation/MultiThread.h"
#include "RenderCommandFence.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class RenderThreadFrameSync
    {
    public:

        /**
         * called by main thread to sync with render thread.
         */
        static void Sync();

    private:
        static RenderCommandFence Fence_[2];
        static int FenceIndex_;

    };
}

