
#include "RunnableThreadWin.h"

using namespace mikasa::Runtime::Foundation;

RunnableThreadWin::RunnableThreadWin(std::string threadName, ThreadPriority priority, Runnable *runnable)
        : RunnableThread(std::move(threadName), priority, runnable)
{
    // Create the thread as suspended, so we can ensure ThreadId is initialized and the thread manager knows about the thread before it runs.
    InternalThread_ = CreateThread(
            nullptr,
            0,
            ThreadProc,
            this,
            STACK_SIZE_PARAM_IS_A_RESERVATION | CREATE_SUSPENDED,
            (::DWORD*)&ThreadID_);

    if (InternalThread_ == nullptr)
    {
        Runnable_ = nullptr;
    }
    else
    {
        // resume the thread because we use CREATE_SUSPENDED
        ResumeThread(InternalThread_);

        // wait until the thread finish initialize
        InitSyncEvent_.WaitOne();
    }
}


void RunnableThreadWin::SetThreadPriority(ThreadPriority priority)
{

}

void RunnableThreadWin::Suspend()
{

}

void RunnableThreadWin::Kill()
{

}

void RunnableThreadWin::WaitForCompletion()
{

}


/**
 * if a thread crash, process the error message and exit the application.
 */
uint32 RunnableThreadWin::GuardedRun()
{
    uint32 ExitCode = 0;
    try
    {
        ExitCode = Run();
        return ExitCode;
    }
    catch(const std::exception& e)
    {
        Logger::Error("RunnableThread %s crashed with exception %s", ThreadName_.c_str(), e.what());
        exit(ApplicationExitCode::ThreadCrash);
    }
}


uint32 RunnableThreadWin::Run()
{
    uint32 exitCode = 1;
    if (Runnable_->Init())
    {
        InitSyncEvent_.Set();
        exitCode = Runnable_->Run();
        Runnable_->Exit();
    }
    else
    {
        InitSyncEvent_.Set();
    }
    return exitCode;
}


