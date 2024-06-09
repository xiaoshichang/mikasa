
#include "RenderCommandQueue.h"
#include "RenderCommandBase.h"

using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

RenderCommandQueue::RenderCommandQueue()
    : InternalQueue_(512)
{

}

void RenderCommandQueue::Enqueue(RenderCommandBase *command)
{
    auto ok = InternalQueue_.push(command);
    MIKASA_ASSERT(ok);
}

RenderCommandBase *RenderCommandQueue::Dequeue()
{
    RenderCommandBase* command = nullptr;
    auto got = InternalQueue_.pop(command);
    if (got)
    {
        return command;
    }
    else
    {
        return nullptr;
    }
}

