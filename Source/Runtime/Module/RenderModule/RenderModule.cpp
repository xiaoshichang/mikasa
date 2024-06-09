
#include "RenderModule.h"
#include "RenderThreadRunnable.h"
#include "Runtime/Core/Render/RenderCommand/RenderCommandQueue.h"
#include "Runtime/Core/Render/RenderCommand/RenderCommandCreator.h"
#include "Runtime/Core/Render/RenderDevice/RenderDevice.h"

using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Core;
using namespace mikasa::Runtime::Foundation;

Runnable* RenderModule::RenderThreadRunnable_;
RunnableThread* RenderModule::RenderThread_;
RenderCommandQueue* RenderModule::RenderCommandQueue_;

void RenderModule::Init(const ApplicationInitParam &param, const WindowHandler& windowHandler)
{
    // construct command queue.
    RenderCommandQueue_ = new RenderCommandQueue();
    RenderCommandCreator::Init(RenderCommandQueue_);

    // construct render thread runnable data.
    RenderThreadRunnableInitParam threadParam;
    threadParam.RenderCommandQueue = RenderCommandQueue_;
    threadParam.ApplicationInitParam = param;
    threadParam.WindowHandler = windowHandler;
    RenderThreadRunnable_ = new RenderThreadRunnable(threadParam);

    // construct render thread with runnable data.
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

    MIKASA_ASSERT(RenderThreadRunnable_ != nullptr);
    delete RenderThreadRunnable_;
    RenderThreadRunnable_ = nullptr;

    RenderCommandCreator::UnInit();

    MIKASA_ASSERT(RenderCommandQueue_ != nullptr);
    delete RenderCommandQueue_;
    RenderCommandQueue_ = nullptr;
    Logger::Info("RenderModule UnInit ok.");

}
