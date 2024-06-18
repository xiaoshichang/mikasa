
#include "RenderCommandQueue.h"
#include "RenderCommandBase.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

// todo: use dynamic size lock-free queue.
boost::lockfree::spsc_queue<RenderCommandBase*> RenderCommandQueue::CommandQueue(1024 * 10);

void RenderCommandQueue::EnqueueOneRenderCommand(RenderCommandBase *command)
{
    auto ok = CommandQueue.push(command);
    MIKASA_ASSERT(ok);
}

RenderCommandBase *RenderCommandQueue::Dequeue()
{
    RenderCommandBase* command = nullptr;
    auto got = CommandQueue.pop(command);
    if (got)
    {
        return command;
    }
    else
    {
        return nullptr;
    }
}

