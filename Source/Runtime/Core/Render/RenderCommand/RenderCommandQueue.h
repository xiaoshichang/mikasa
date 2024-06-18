#pragma once
#include "boost/lockfree/spsc_queue.hpp"
#include "Runtime/Foundation/Foundation.h"
#include "RenderCommandBase.h"


namespace mikasa::Runtime::Core
{
    class RenderCommandQueue
    {

    public:
        static void EnqueueOneRenderCommand(RenderCommandBase* command);
        static RenderCommandBase* Dequeue();

    private:
        static boost::lockfree::spsc_queue<RenderCommandBase*> CommandQueue;
    };

#define ENQUEUE_LAMBDA_RENDER_COMMAND(L) \
    auto command = new RenderCommandLambda(std::move(lambda));  \
    RenderCommandQueue::EnqueueOneRenderCommand(command);
}


