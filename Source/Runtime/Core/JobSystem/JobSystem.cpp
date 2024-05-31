
#include "JobSystem.h"
#include "JobSystemGlobalQueue.h"
#include "JobWorker.h"
#include "Job.h"


#include <string>
#include <format>

using namespace mikasa::Runtime::Core;

JobSystem::JobSystem(const JobSystemInitParam &param)
    : InitParam_(param)
{
    // create work queue
    {
        GlobalQueue_ = new JobSystemGlobalQueue();
        Job::GlobalQueue = GlobalQueue_;
    }

    // create workers
    {
        for(int i = 0; i < InitParam_.WorkerThreadCount; i++)
        {
            JobWorkerInitParam workerParam{};
            workerParam.ThreadName = std::format("Worker{}", i);
            workerParam.ThreadPriority = ThreadPriority::Middle;
            workerParam.RunnableInitParam.GlobalQueue = GlobalQueue_;

            auto worker = new JobWorker(workerParam);
            Workers_.push_back(worker);
        }
    }
}

JobSystem::~JobSystem()
{
    // destroy workers
    {
        for(int i = 0; i < InitParam_.WorkerThreadCount; i++)
        {
            delete Workers_[i];
        }
        Workers_.clear();
    }
    // destroy work queue
    {
        MIKASA_ASSERT(GlobalQueue_ != nullptr);
        delete GlobalQueue_;
        GlobalQueue_ = nullptr;
        Job::GlobalQueue = nullptr;
    }
}
