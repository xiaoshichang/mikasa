#if MIKASA_TARGET_PLATFORM_Window
#pragma once

#include "RunnableThread.h"
#include <windows.h>

namespace mikasa::Runtime::Foundation
{

    class RunnableThreadWin final : public RunnableThread
    {
    private:
        static DWORD __stdcall ThreadProc(LPVOID param)
        {
            auto* thread = (RunnableThreadWin*)param;
            return thread->GuardedRun();
        }

        uint32 GuardedRun();
        uint32 Run();

    public:
        RunnableThreadWin(std::string  threadName, ThreadPriority priority, Runnable* runnable);

        void SetThreadPriority(ThreadPriority priority) override;

        void Suspend() override;

        void Kill() override;

        void WaitForCompletion() override;

    private:
        HANDLE InternalThread_ = 0;

    };

}


#endif