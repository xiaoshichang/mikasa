#pragma once
#include "boost/lockfree/spsc_queue.hpp"
#include "Runtime/Foundation/Foundation.h"

namespace mikasa::Runtime::Core
{
    class RenderCommandBase;
    class RenderCommandQueue
    {
    public:
        RenderCommandQueue();
        ~RenderCommandQueue() = default;


    public:
        void Enqueue(RenderCommandBase* command);
        RenderCommandBase* Dequeue();

    private:
        boost::lockfree::spsc_queue<RenderCommandBase*> InternalQueue_;
    };
}


