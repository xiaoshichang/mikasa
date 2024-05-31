#include "ApplicationBase.h"
#include "Runtime/Module/SystemInfoModule/SystemInfoModule.h"
#include "Runtime/Module/MemoryManagementModule/MemoryManagementModule.h"
#include "Runtime/Module/RenderModule/RenderModule.h"

using namespace mikasa::Runtime::Application;
using namespace mikasa::Runtime::Module;

void ApplicationBase::Init(const ApplicationInitParam& info)
{
    Logger::Init(LogSink::Console|LogSink::File, info.LogDir, info.LogPath);
    SystemInfoModule::Init(info);
    SystemInfoModule::OutputInfo();
    MemoryManagementModule::Init(info);
    RenderModule::Init(info);

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
    RenderModule::UnInit();
    MemoryManagementModule::UnInit();
    SystemInfoModule::Uninit();
    Logger::UnInit();
}

void ApplicationBase::TryQuit()
{
    IsApplicationQuit_ = true;
}
