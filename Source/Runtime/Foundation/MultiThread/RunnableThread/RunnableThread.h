#pragma once
#include <string>
#include <utility>
#include "Runnable.h"
#include "../../Foundation.h"
#include "../ManualResetEvent.h"


namespace mikasa::Runtime::Foundation
{
    enum ThreadPriority
    {
        Low,
        Middle,
        High
    };

    class RunnableThread
    {
    public:
        RunnableThread(std::string threadName, ThreadPriority priority, Runnable* runnable)
            : ThreadName_(std::move(threadName))
            , ThreadPriority_(priority)
            , Runnable_(runnable)
        {
        }

        virtual ~RunnableThread() = default;

        virtual void SetThreadPriority(ThreadPriority priority) = 0;
        virtual void Suspend() = 0;
        virtual void Resume() = 0;
        virtual void Kill(bool wait) = 0;
        virtual void WaitForCompletion() = 0;
        uint32 GetThreadID() const { return ThreadID_;}


    protected:
        Runnable* Runnable_;
        std::string ThreadName_;
        ThreadPriority ThreadPriority_;
        ManualResetEvent InitSyncEvent_;

        uint32 ThreadID_ = 0;

    };
}