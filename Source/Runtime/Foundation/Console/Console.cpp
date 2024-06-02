
#include "Console.h"
#include "../Foundation.h"
#include "ConsoleInputRunnable.h"

#if MIKASA_TARGET_PLATFORM_Window
#include "Platform/Windows/ConsoleWin.h"
#else
#error
#endif

using namespace mikasa::Runtime::Foundation;

Console* Console::Instance_ = nullptr;
CriticalSection Console::ConsoleProtection;
RunnableThread* Console::InputThread_ = nullptr;
Runnable* Console::InputRunnable_ = nullptr;


Console::Console()
{


}

Console::~Console()
{

}


void Console::Init()
{
    MIKASA_ASSERT(Instance_ == nullptr);
    Instance_ = CreatePlatformIndependentConsole();
    InputRunnable_ = new ConsoleInputRunnable(Instance_);
    InputThread_ = PlatformIndependentRunnableThread::CreatePlatformIndependentRunnableThread(
            "ConsoleInput",
            ThreadPriority::Middle,
            InputRunnable_);
}

void Console::UnInit()
{
    MIKASA_ASSERT(InputThread_ != nullptr);
    InputThread_->Kill(true);
    delete InputThread_;
    InputThread_ = nullptr;

    MIKASA_ASSERT(InputRunnable_ != nullptr);
    delete InputRunnable_;
    InputRunnable_ = nullptr;

    MIKASA_ASSERT(Instance_ != nullptr);
    delete Instance_;
    Instance_ = nullptr;
}

Console* Console::CreatePlatformIndependentConsole()
{
#if MIKASA_TARGET_PLATFORM_Window
    return new ConsoleWin();
#else
#error
#endif
}


void Console::OnOutputString(const std::string &s, ConsoleTextColor color)
{
    Instance_->InternalOutputString(s, color);
}

