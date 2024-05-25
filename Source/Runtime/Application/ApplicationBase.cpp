#include "ApplicationBase.h"
#include "Runtime/Module/SystemInfoModule/SystemInfoModule.h"
#include <thread>

using namespace mikasa::Runtime::Application;
using namespace mikasa::Runtime::Module;

void ApplicationBase::Init(const ApplicationInitParam& info)
{
    Logger::Init(info.LogDir, info.LogPath);
    SystemInfoModule::Init(info);
    SystemInfoModule::OutputInfo();
}

void ApplicationBase::Run()
{
    while (!IsApplicationQuit_)
    {
        Logger::Info("run...");
        Sleep(1000);
    }
}

void ApplicationBase::UnInit()
{
    SystemInfoModule::Uninit();
    Logger::UnInit();
}

void ApplicationBase::TryQuit()
{
    IsApplicationQuit_ = true;
}
