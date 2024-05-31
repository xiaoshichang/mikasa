#pragma once

#include "Runtime/Foundation/MultiThread.h"

using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    class JobSystemGlobalQueue;

    struct JobWorkerRunnableInitParam
    {
        JobSystemGlobalQueue* GlobalQueue = nullptr;
    };


    class JobWorkerRunnable : public Runnable
    {
    public:
        explicit JobWorkerRunnable(const JobWorkerRunnableInitParam& param);
        ~JobWorkerRunnable() override = default;

        bool Init() override;

        uint32 Run() override;

        void Exit() override;

        void Stop() override;

    private:
        bool StopWorking_ = false;
        JobSystemGlobalQueue* GlobalQueue_;
    };

}
