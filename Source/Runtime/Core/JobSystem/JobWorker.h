#pragma once
#include <string>
#include "Runtime/Foundation/MultiThread.h"
#include "Runtime/Foundation/Foundation.h"
#include "JobWorkerRunnable.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    struct JobWorkerInitParam
    {
        std::string ThreadName;
        ThreadPriority ThreadPriority;

        JobWorkerRunnableInitParam RunnableInitParam;
    };

    class JobWorker
    {
    public:
        explicit JobWorker(const JobWorkerInitParam& param);
        JobWorker(const JobWorker& copy) = delete;
        ~JobWorker();


    private:
        JobWorkerRunnable* Runnable_;
        RunnableThread* Thread_;

    };
}

