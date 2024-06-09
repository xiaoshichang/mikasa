
#include <codecvt>
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
        InitSyncEvent_.Wait();

        // set ThreadPriority after runnable init.
        SetThreadPriority(priority);
    }
}


RunnableThreadWin::~RunnableThreadWin()
{
    if (InternalThread_)
    {
        Kill(true);
    }
}


void RunnableThreadWin::SetThreadPriority(ThreadPriority priority)
{
    MIKASA_ASSERT(InternalThread_ != nullptr);
    ::SetThreadPriority(InternalThread_, TranslateThreadPriority(priority));
}

void RunnableThreadWin::Suspend()
{
    MIKASA_ASSERT(InternalThread_ != nullptr);
    SuspendThread(InternalThread_);
}

void RunnableThreadWin::Resume()
{
    MIKASA_ASSERT(InternalThread_ != nullptr);
    ResumeThread(InternalThread_);
}

void RunnableThreadWin::Kill(bool wait)
{
    MIKASA_ASSERT(InternalThread_ != nullptr);
    Runnable_->Stop();
    if (wait)
    {
        WaitForSingleObject(InternalThread_, INFINITE);
    }
    CloseHandle(InternalThread_);
    InternalThread_ = nullptr;
}

void RunnableThreadWin::WaitForCompletion()
{
    MIKASA_ASSERT(InternalThread_ != nullptr);
    WaitForSingleObject(InternalThread_, INFINITE);
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
    boost::log::core::get()->add_thread_attribute("ThreadName", boost::log::attributes::constant< std::string >(ThreadName_));
    uint32 exitCode = 1;

#ifdef MIKASA_BUILDTYPE_DEBUG
    std::wstring wsTmp(ThreadName_.begin(), ThreadName_.end());
    SetThreadDescription(GetCurrentThread(), wsTmp.c_str());
#endif

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

int RunnableThreadWin::TranslateThreadPriority(ThreadPriority priority)
{
    switch (priority)
    {
        case ThreadPriority::High:      return THREAD_PRIORITY_ABOVE_NORMAL;
        case ThreadPriority::Middle:    return THREAD_PRIORITY_NORMAL;
        case ThreadPriority::Low:       return THREAD_PRIORITY_BELOW_NORMAL;
    }
    MIKASA_ASSERT(false);
    throw;
}



