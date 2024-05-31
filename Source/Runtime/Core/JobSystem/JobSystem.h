#pragma once
#include <vector>

#include "Runtime/Foundation/Foundation.h"
#include "Runtime/Foundation/MultiThread.h"


using namespace mikasa::Runtime::Foundation;

namespace mikasa::Runtime::Core
{
    struct JobSystemInitParam
    {
        int WorkerThreadCount;
    };


    class JobWorker;
    class JobSystemGlobalQueue;

    class JobSystem
    {
    public:
        explicit JobSystem(const JobSystemInitParam& param);
        ~JobSystem();


    private:
        JobSystemInitParam InitParam_;
        std::vector<JobWorker*> Workers_;
        JobSystemGlobalQueue* GlobalQueue_;
    };
}
