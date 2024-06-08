#include <format>
#include "Application.h"
#include "Runtime/Framework/MainWindow/MainWindow.h"
#include "Runtime/Foundation/Console/Console.h"

#include "Runtime/Module/SystemInfoModule/SystemInfoModule.h"
#include "Runtime/Module/MemoryManagementModule/MemoryManagementModule.h"
#include "Runtime/Module/RenderModule/RenderModule.h"
#include "Runtime/Module/JobSystemModule/JobSystemModule.h"
#include "Runtime/Module/ScriptModule/ScriptModule.h"

using namespace mikasa::Runtime::Framework;
using namespace mikasa::Runtime::Module;
using namespace mikasa::Runtime::Foundation;

void Application::Init(const ApplicationInitParam& info)
{

#if MIKASA_BUILDTYPE_DEBUG
    Console::Init();
#endif

    MainWindow::Init(this, info);

#if MIKASA_BUILDTYPE_DEBUG
    Logger::Init(LogSink::ConsoleBackend | LogSink::FileBackend, info.LogDir, info.LogPath);
#else
    Logger::Init(LogSink::FileBackend, info.LogDir, info.LogPath);
#endif

    SystemInfoModule::Init(info);
    SystemInfoModule::OutputInfo();
    MemoryManagementModule::Init(info);
    ScriptModule::Init(info);
    JobSystemModule::Init(info);
    RenderModule::Init(info);

}

void Application::Run()
{
    int a;
    while (!IsApplicationQuit_)
    {
        DispatchOSMessage();
#if MIKASA_BUILDTYPE_DEBUG
        ScriptModule::ConsumeConsoleInput();
#endif
    }
}

void Application::UnInit()
{
    RenderModule::UnInit();
    JobSystemModule::UnInit();
    ScriptModule::UnInit();
    MemoryManagementModule::UnInit();
    SystemInfoModule::Uninit();
    Logger::UnInit();

    MainWindow::UnInit();
#if MIKASA_BUILDTYPE_DEBUG
    Console::UnInit();
#endif
}

void Application::RequestQuit()
{
    IsApplicationQuit_ = true;
}
