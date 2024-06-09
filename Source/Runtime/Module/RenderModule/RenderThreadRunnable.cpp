
#include "RenderThreadRunnable.h"
#include "Runtime/Core/Render/RenderCommand/RenderCommandBase.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"

using namespace mikasa::Runtime::Module;

RenderThreadRunnable::RenderThreadRunnable(const RenderThreadRunnableInitParam &param)
    : InitParam_(param)
    , RenderCommandQueue_(param.RenderCommandQueue)
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
        auto command = RenderCommandQueue_->Dequeue();
        if (command != nullptr)
        {
            command->Execute();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds (1));
        }
    }
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

