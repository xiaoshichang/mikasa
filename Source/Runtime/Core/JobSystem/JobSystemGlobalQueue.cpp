
#include "JobSystemGlobalQueue.h"
#include "Job.h"

using namespace mikasa::Runtime::Core;

JobSystemGlobalQueue::JobSystemGlobalQueue()
    : InternalQueue_(100)
{
}

bool JobSystemGlobalQueue::Enqueue(Job *job)
{
    auto ok = InternalQueue_.push(job);
    MIKASA_ASSERT(ok);
    return true;
}

Job *JobSystemGlobalQueue::Dequeue()
{
    Job* job = nullptr;
    auto got = InternalQueue_.pop(job);
    if (got)
    {
        return job;
    }
    else
    {
        return nullptr;
    }
}


