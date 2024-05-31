
#include "Job.h"
#include "JobSystemGlobalQueue.h"

using namespace mikasa::Runtime::Core;

JobSystemGlobalQueue* Job::GlobalQueue = nullptr;

Job::Job() : State_(JobState::Created)
{

}

void Job::Schedule()
{
    State_ = JobState::Scheduling;
    GlobalQueue->Enqueue(this);
}

void Job::OnSchedule()
{
    State_ = JobState::Executing;
    try
    {
        Execute();
        State_ = JobState::Finish;
        CompletionEvent.Set();
    }
    catch (const std::exception& e)
    {
        State_ = JobState::Exception;
        CompletionEvent.Set();
    }
}

void Job::WaitCompletion()
{
    if (State_ == JobState::Created)
    {
        Logger::Warning("plz Schedule the job before WaitCompletion");
        return;
    }
    CompletionEvent.Wait();
}




