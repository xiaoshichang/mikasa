
#include "JobWorker.h"

using namespace mikasa::Runtime::Core;

JobWorker::JobWorker(const JobWorkerInitParam& param)
{
    Runnable_ = new JobWorkerRunnable(param.RunnableInitParam);
    Thread_ = PlatformIndependentRunnableThread::CreatePlatformIndependentRunnableThread(
            param.ThreadName,
            param.ThreadPriority,
            Runnable_
            );
}

JobWorker::~JobWorker()
{
    Thread_->Kill(true);
    delete Thread_;
    Thread_ = nullptr;

    delete Runnable_;
    Runnable_ = nullptr;
}
