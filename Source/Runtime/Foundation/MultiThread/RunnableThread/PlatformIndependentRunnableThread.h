#pragma once
#include "RunnableThread.h"

#include <utility>

#if MIKASA_TARGET_PLATFORM_Window
#include "RunnableThreadWin.h"
#endif


namespace mikasa::Runtime::Foundation
{
    class PlatformIndependentRunnableThread
    {
    public:
        static RunnableThread* CreatePlatformIndependentRunnableThread(std::string threadName, ThreadPriority priority, Runnable* runnable)
        {
            RunnableThread* thread;
#if MIKASA_TARGET_PLATFORM_Window
            thread = new RunnableThreadWin(std::move(threadName), priority, runnable);
#else
#error "unsupported platform"
#endif
            return thread;
        }
    };

}
