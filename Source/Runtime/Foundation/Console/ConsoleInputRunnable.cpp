

#include "ConsoleInputRunnable.h"
#include "Console.h"

using namespace mikasa::Runtime::Foundation;


ConsoleInputRunnable::ConsoleInputRunnable(Console *console)
    : Console_(console)
{
}


bool ConsoleInputRunnable::Init()
{
    Console_->InputPrefix();
    return true;
}

uint32 ConsoleInputRunnable::Run()
{
    while (Running_)
    {
        Console_->ProcessInputEvents();
    }
    return 0;
}

void ConsoleInputRunnable::Exit()
{

}

void ConsoleInputRunnable::Stop()
{
    Running_ = false;
}
