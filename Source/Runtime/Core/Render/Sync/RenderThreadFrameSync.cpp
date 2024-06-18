
#include "RenderThreadFrameSync.h"
#include "Runtime/Foundation/Foundation.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

RenderCommandFence RenderThreadFrameSync::Fence_[2];
int RenderThreadFrameSync::FenceIndex_ = 0;

void RenderThreadFrameSync::Sync()
{
    auto& fence = Fence_[FenceIndex_];
    fence.BeginFence();

    FenceIndex_ = (FenceIndex_ + 1) % 2;

    Fence_[FenceIndex_].Wait();
}
