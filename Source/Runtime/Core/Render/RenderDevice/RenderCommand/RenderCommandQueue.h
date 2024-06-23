#pragma once
#include "boost/lockfree/spsc_queue.hpp"
#include "Runtime/Foundation/Foundation.h"
#include "RenderCommandBase.h"


namespace mikasa::Runtime::Core
{
    class RenderCommandQueue
    {

    public:
        RenderCommandQueue();
        void EnqueueOneRenderCommand(RenderCommandBase* command);
        RenderCommandBase* Dequeue();

    private:

        // todo: use dynamic size lock-free queue.
        boost::lockfree::spsc_queue<RenderCommandBase*> CommandQueue;
    };

}


