
#include "RenderCommandCreator.h"
#include "RenderCommandQueue.h"

using namespace mikasa::Runtime::Core;

RenderCommandQueue* RenderCommandCreator::CommandQueue_ = nullptr;


void RenderCommandCreator::Init(RenderCommandQueue* queue)
{
    MIKASA_ASSERT(CommandQueue_ == nullptr);
    CommandQueue_ = queue;
}

void RenderCommandCreator::UnInit()
{
    MIKASA_ASSERT(CommandQueue_ != nullptr);
    CommandQueue_ = nullptr;
}

void RenderCommandCreator::Enqueue_SetViewportCmd()
{

}
