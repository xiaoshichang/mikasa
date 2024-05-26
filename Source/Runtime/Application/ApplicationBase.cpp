#include "ApplicationBase.h"
#include "Runtime/Module/SystemInfoModule/SystemInfoModule.h"
#include "Runtime/Module/MemoryManagementModule/MemoryManagementModule.h"

using namespace mikasa::Runtime::Application;
using namespace mikasa::Runtime::Module;

void ApplicationBase::Init(const ApplicationInitParam& info)
{
    Logger::Init(info.LogDir, info.LogPath);
    SystemInfoModule::Init(info);
    SystemInfoModule::OutputInfo();
    MemoryManagementModule::Init(info);
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
    MemoryManagementModule::UnInit();
    SystemInfoModule::Uninit();
    Logger::UnInit();
}

void ApplicationBase::TryQuit()
{
    IsApplicationQuit_ = true;
}
