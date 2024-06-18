
#include "RenderThreadRunnable.h"

#include <utility>
#include "Runtime/Core/Render/RenderCommand/RenderCommandBase.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"

using namespace mikasa::Runtime::Module;

RenderThreadRunnable::RenderThreadRunnable(RenderThreadRunnableInitParam param)
    : InitParam_(std::move(param))
    , Rendering_(true)
{

}


bool RenderThreadRunnable::Init()
{
    RenderDevice::Init(InitParam_.ApplicationInitParam, InitParam_.WindowHandler);
    Logger::Info("RenderThread Init.");
    return true;
}

uint32 RenderThreadRunnable::Run()
{
    while (Rendering_)
    {
        bool processed = RenderDevice::ProcessOneRenderCommand();
        if (!processed)
        {
            // https://en.cppreference.com/w/cpp/thread/yield
            // https://stackoverflow.com/questions/11048946/stdthis-threadyield-vs-stdthis-threadsleep-for
            std::this_thread::yield();
        }
    }

    // after thread stop, flush all remain commands.
    RenderDevice::FlushAllRenderCommand();
    return 0;
}

void RenderThreadRunnable::Exit()
{
    RenderDevice::UnInit();
    Logger::Info("RenderThread Exit.");
}

void RenderThreadRunnable::Stop()
{
    Rendering_ = false;
    Logger::Info("RenderThread Stop.");
}

