
#include "RenderCommandFence.h"
#include "../RenderCommand/RenderCommandQueue.h"


using namespace mikasa::Runtime::Core;

RenderCommandFence::RenderCommandFence()
    : Event_(true)
{
}

void RenderCommandFence::BeginFence()
{
    Event_.Reset();
    auto lambda = [this]()
    {
        Event_.Set();
    };
    ENQUEUE_LAMBDA_RENDER_COMMAND(lambda);
}

void RenderCommandFence::Wait()
{
    Event_.Wait();
}


