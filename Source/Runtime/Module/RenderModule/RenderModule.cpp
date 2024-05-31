
#include "RenderModule.h"
#include "RenderThreadRunnable.h"

using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Foundation;

Runnable* RenderModule::RenderThreadRunnable_;
RunnableThread* RenderModule::RenderThread_;

void RenderModule::Init(const ApplicationInitParam &info)
{
    RenderThreadRunnable_ = new RenderThreadRunnable();
    RenderThread_ = PlatformIndependentRunnableThread::CreatePlatformIndependentRunnableThread(
            "RenderThread",
            ThreadPriority::Middle,
            RenderThreadRunnable_);

}

void RenderModule::UnInit()
{
    delete RenderThread_;
    RenderThread_ = nullptr;

    delete RenderThreadRunnable_;
    RenderThreadRunnable_ = nullptr;
}
