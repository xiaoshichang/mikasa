
#include "RenderModule.h"
#include "RenderThreadRunnable.h"
#include "Runtime/Core/Render/RenderCommandQueue.h"

using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

Runnable* RenderModule::RenderThreadRunnable_;
RunnableThread* RenderModule::RenderThread_;
RenderCommandQueue* RenderModule::RenderCommandQueue_;


void RenderModule::Init(const ApplicationInitParam &info)
{
    RenderCommandQueue_ = new RenderCommandQueue();

    RenderThreadRunnableInitParam param{};
    param.RenderCommandQueue = RenderCommandQueue_;
    RenderThreadRunnable_ = new RenderThreadRunnable(param);

    RenderThread_ = PlatformIndependentRunnableThread::CreatePlatformIndependentRunnableThread(
            "Render",
            ThreadPriority::Middle,
            RenderThreadRunnable_);

    Logger::Info("RenderModule Init ok.");
}

void RenderModule::UnInit()
{
    MIKASA_ASSERT(RenderThread_ != nullptr);
    RenderThread_->Kill(true);
    delete RenderThread_;
    RenderThread_ = nullptr;

    delete RenderThreadRunnable_;
    RenderThreadRunnable_ = nullptr;

    delete RenderCommandQueue_;
    RenderCommandQueue_ = nullptr;
    Logger::Info("RenderModule UnInit ok.");

}
