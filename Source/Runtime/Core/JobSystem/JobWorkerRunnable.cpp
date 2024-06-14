
#include "JobWorkerRunnable.h"
#include "JobSystemGlobalQueue.h"
#include "Job.h"

using namespace mikasa::Runtime::Core;

JobWorkerRunnable::JobWorkerRunnable(const JobWorkerRunnableInitParam& param)
    : GlobalQueue_(param.GlobalQueue)
{
}

bool JobWorkerRunnable::Init()
{
    Logger::Info("%s Init.", Thread_->GetThreadName().c_str());
    return true;
}

uint32 JobWorkerRunnable::Run()
{
    while (!StopWorking_)
    {
        auto job = GlobalQueue_->Dequeue();
        if (job != nullptr)
        {
            job->OnSchedule();
        }
        else
        {
            std::this_thread::yield();
        }
    }
    return 0;
}

void JobWorkerRunnable::Exit()
{
    Logger::Info("%s Exit.", Thread_->GetThreadName().c_str());
}

void JobWorkerRunnable::Stop()
{
    Logger::Info("%s Stop.", Thread_->GetThreadName().c_str());
    StopWorking_ = true;
}


