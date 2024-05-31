#pragma once
#include "Runtime/Foundation/MultiThread.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class JobSystemGlobalQueue;

    enum JobState
    {
        Created,
        Scheduling,
        Executing,
        Finish,
        Exception
    };

    class Job
    {
    public:
        Job();
        virtual ~Job() = default;
        static JobSystemGlobalQueue* GlobalQueue;

    public:
        void Schedule();
        void OnSchedule();
        void WaitCompletion();

    protected:
        virtual void Execute() = 0;

    private:
        JobState State_;
        ManualResetEvent CompletionEvent;

    };
}

